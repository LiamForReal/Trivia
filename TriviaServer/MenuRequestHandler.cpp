#include "MenuRequestHandler.h"
#include <algorithm>

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& rhf, LoggedUser user) : _RHF(rhf)
{
    _user = user;
    rr = RequestResult();
}

MenuRequestHandler::~MenuRequestHandler() {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& ri)
{
    return ri.id >= LOGOUT_RC && ri.id <= GET_PERSONAL_STATS_RC;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& ri)
{
    switch (ri.id)
    {
    case LOGOUT_RC:
        return signout(ri);
        break;
    case GET_ROOMS_RC:
        return getRooms(ri);
        break;
    case GET_PLAYERS_IN_ROOM_RC:
        return getPlayersInRoom(ri);
        break;
    case JOIN_ROOM_RC:
        return joinRoom(ri);
        break;
    case CREATE_ROOM_RC:
        return createRoom(ri);
        break;
    case GET_HIGH_SCORE_RC:
        return getHighScore(ri);
        break;
    case GET_PERSONAL_STATS_RC:
        return getPersonalStats(ri);
        break;
    }
}

RequestResult MenuRequestHandler::signout(RequestInfo ri)
{
    LogoutResponse lr = LogoutResponse();
    try
    {
        _RHF.getLoginMeneger().logout(_user.getUserName());
        lr.status = LOGOUT_STATUS;
    } 
    catch (std::runtime_error e)
    {
        lr.status = LOGOUT_ERROR;
    }
    rr.buffer = JsonResponsePacketSerializer::serializeResponse(lr);
    rr.newHandler = _RHF.creatLoginRequestHandler();
    this->_user.setUserName("");
    std::cout << "im here3\n";
    return rr;
}

// FIXED HOPEFULLY
RequestResult MenuRequestHandler::getRooms(RequestInfo ri) {
    GetRoomsResponse grr;
    grr.status = GET_ROOMS_STATUS;

    rr.buffer = std::vector<unsigned char>();
    rr.newHandler = _RHF.createMenuRequestHandler(_user);

    // Check if there are no rooms and return early if so
    if (_RHF.getRoomManager().getRooms().empty()) {
        rr.buffer = JsonResponsePacketSerializer::serializeResponse(grr);
        return rr;
    }

    std::vector<RoomData> rd = _RHF.getRoomManager().getRooms();

    std::cout << "START COPYING PROCESS" << std::endl;

    grr.rooms = rd; // Direct assignment of the vector

    std::cout << "COPIED ROOM_DATA VECTOR WITH SUCCESS" << std::endl;

    std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeResponse(grr);
    rr.buffer = buffer; // Direct assignment of the vector

    std::cout << "COPIED BYTES VECTOR WITH SUCCESS" << std::endl;

    return rr;
}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo ri) //go over
{
    rr.buffer = std::vector<unsigned char>();
    std::vector<unsigned char> buffer;
    unsigned int status = 0;
    Room room = Room();
    GetPlayersInRoomRequest gpr = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(ri.buffer);
    try
    {
        room = _RHF.getRoomManager().getRoom(gpr.roomId);
        if (_RHF.getRoomManager().isLegalRoom(gpr.roomId))
            status = GET_PLAYERS_IN_ROOM_STATUS;
        else status = GET_PLAYERS_IN_ROOM_ERROR;
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        status = GET_PLAYERS_IN_ROOM_ERROR;
    }

    GetPlayersInRoomResponse gpre;
    gpre.status = status;
    gpre.players = room.getAllUsers();
    buffer = JsonResponsePacketSerializer::serializeResponse(gpre);
    std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));

    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo ri)
{
    vector<string> playerStats = _RHF.getStatisticsManager().getUserStatistics(_user.getUserName());
    GetPersonalStatsResponse gpsr = GetPersonalStatsResponse();
    gpsr.status = GET_PERSONAL_STATS_STATUS;
    gpsr.statistics = playerStats;
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    rr.buffer = JsonResponsePacketSerializer::serializeResponse(gpsr);
    return rr;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo ri) //go over
{
    vector<string> HighScores = _RHF.getStatisticsManager().getHighScore();
    int i = 0, size = 0, j = 0;
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    GetHighScoreResponse ghsr = GetHighScoreResponse();
    ghsr.status = GET_HIGH_SCORE_STATUS;
    ghsr.statistics = vector<string>();
    std::copy(HighScores.begin(), HighScores.end(), std::back_inserter(ghsr.statistics));

    rr.buffer = JsonResponsePacketSerializer::serializeResponse(ghsr);
    return rr;
}

// NOTE for future safety from hacks: check if player is already in room,
// and return ERROR if positive.
RequestResult MenuRequestHandler::joinRoom(RequestInfo ri)//go over
{
    rr.buffer = std::vector<unsigned char>();
    std::vector<unsigned char> buffer;
    unsigned int status = 0;
    JoinRoomRequest jrr = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(ri.buffer);
    try
    {
        Room room = _RHF.getRoomManager().getRoom(jrr.roomId);
        if (_RHF.getRoomManager().isLegalRoom(jrr.roomId) && (ACTIVE_ROOM == _RHF.getRoomManager().getRoomState(jrr.roomId)))
        {
            room.addUser(_user);
            status = JOIN_ROOM_STATUS;
        } 
        else status = JOIN_ROOM_ERROR;
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        status = JOIN_ROOM_ERROR;
    }
    JoinRoomResponse jrre;
    jrre.status = status;
    buffer = JsonResponsePacketSerializer::serializeResponse(jrre);
    std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));

    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo ri)
{
    CreateRoomResponse crre = CreateRoomResponse();
    CreateRoomRequest crr = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(ri.buffer);
    try
    {
        RoomData roomData = RoomData(_RHF.getRoomManager().getRooms().size() + 1, crr.roomName, crr.maxUsers, crr.questionsCount, crr.answerTimeout, false);
        vector<RoomData> rooms = _RHF.getRoomManager().getRooms();
        crre.status = CREATE_ROOM_STATUS;
        for (auto it = rooms.begin(); it != rooms.end(); ++it)
        {
            if (it->id == roomData.id || it->name == roomData.name)
            {
                crre.status = CREATE_ROOM_ERROR;
            }
        }

        if (crre.status == CREATE_ROOM_STATUS)
        {
            _RHF.getRoomManager().createRoom(_user, roomData);
            std::cout << "befor exception!!\n";
            _RHF.getRoomManager().getRoom(roomData.id).addUser(_user);
        }
            
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        crre.status = CREATE_ROOM_ERROR;
    }
    rr.buffer = JsonResponsePacketSerializer::serializeResponse(crre);
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}