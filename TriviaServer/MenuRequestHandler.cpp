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

// TOFIX
RequestResult MenuRequestHandler::getRooms(RequestInfo ri) //go over
{
    std::vector<unsigned char> buffer;
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    if (_RHF.getRoomManager().getRooms().size() <= 0)
    {
        return rr;
    }
    vector<RoomData> rd = _RHF.getRoomManager().getRooms();
    string tmp = "{";
    for (int i = 0; i < rd.size(); i++)
    {

        tmp += "[" + std::to_string(rd[i].id) + "," + rd[i].name + "," + std::to_string(rd[i].maxPlayers)
            + "," + std::to_string(rd[i].numOfQuestionsInGame) + "," + std::to_string(rd[i].timePerQuestion) + "],";
    }
    tmp = tmp.substr(0, tmp.size() - 1);
    unsigned char* tmp2 = new unsigned char[tmp.size() + 1];
    tmp2[tmp.size()] = '\0';
    std::copy(tmp.begin(), tmp.end(), tmp2);
    for (int i = 0; i < buffer.size(); i++)
    {
        rr.buffer[i] = buffer[i];
    }
    delete[] tmp2;
    return rr;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo ri) //go over
{
    rr.buffer = std::vector<unsigned char>();
    std::vector<unsigned char> buffer;
    unsigned int status = 0;
    GetPlayersInRoomRequest gpr = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(ri.buffer);
    Room room = _RHF.getRoomManager().getRoom(gpr.roomId);
    if (_RHF.getRoomManager().isLegalRoom(gpr.roomId))
        status = GET_PLAYERS_IN_ROOM_STATUS;
    else status = GET_PLAYERS_IN_ROOM_ERROR;
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
    Room room = _RHF.getRoomManager().getRoom(jrr.roomId);
    if (_RHF.getRoomManager().isLegalRoom(jrr.roomId) && (ACTIVE_ROOM == _RHF.getRoomManager().getRoomState(jrr.roomId)))
        status = JOIN_ROOM_STATUS;
    else status = JOIN_ROOM_ERROR;
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
    RoomData roomData = RoomData(_RHF.getRoomManager().getRooms().size() + 1, crr.roomName , crr.maxUsers, crr.questionsCount, crr.answerTimeout, false);
    vector<RoomData> rooms = _RHF.getRoomManager().getRooms();
    for (auto it = rooms.begin(); it != rooms.end(); ++it)
    {
        if (it->id == roomData.id || it->name == roomData.name)
        {
            crre.status = CREATE_ROOM_ERROR;
        }
    }

    if (crre.status != CREATE_ROOM_ERROR)
    {
        crre.status = CREATE_ROOM_STATUS;
        _RHF.getRoomManager().createRoom(_user, roomData);
    }
      
    rr.buffer = JsonResponsePacketSerializer::serializeResponse(crre);
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}