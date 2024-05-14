#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& rhf, LoggedUser user) : _RHF(rhf), _user(user)
{
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
    }
    return rr;
}

RequestResult MenuRequestHandler::signout(RequestInfo ri)
{
    LogoutResponse lr;
    std::vector<unsigned char> buffer;
    _RHF.getLoginMeneger().logout(_user.getUserName());
    lr.status = LOGOUT_STATUS;
    rr.buffer = JsonResponsePacketSerializer::serializeResponse(lr);
    rr.newHandler = _RHF.creatLoginRequestHandler();
    this->_user.setUserName("");
    return rr;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo ri)
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

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo ri)
{
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
    std::copy(buffer.begin(), buffer.end(), rr.buffer.begin());
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& ri)
{
    string playerStats = _RHF.getStatisticsManager().getUserStatistics(_user.getUserName());
    unsigned char* tmp = new unsigned char[playerStats.size() + 1];
    std::copy(playerStats.begin(), playerStats.end(), tmp);
    tmp[playerStats.size()] = '\0';
    std::copy(rr.buffer.begin(), rr.buffer.end(), tmp);
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo ri)
{

    vector<string> HighScores = _RHF.getStatisticsManager().getHighScore();
    int i = 0, size = 0, j = 0;
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    string code = std::to_string(GET_HIGH_SCORE_ERROR);
    if (HighScores.size() == 0)
    {
        //std::copy(rr.buffer.begin(), rr.buffer.end(), code);
        return rr;
    }

    for (i = 0; i < HighScores.size(); i++)
        size += HighScores[i].size();

    string tmp = "";

    for (i = 0; i < HighScores.size(); i++)
    {
        for (j = 0; j < HighScores[i].size(); j++)
        {
            HighScores[i][j] = tmp[j];
        }
        tmp += '|';
    }

    unsigned char* tmp2 = new unsigned char[tmp.size() + 1];
    tmp2[tmp.size()] = '\0';
    std::copy(tmp.begin(), tmp.end(), tmp2);
    delete[] tmp2;
    return rr;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo ri)
{
    std::vector<unsigned char> buffer;
    unsigned int status = 0;
    JoinRoomRequest jrr = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(ri.buffer);
    Room room = _RHF.getRoomManager().getRoom(jrr.roomId);
    if (_RHF.getRoomManager().isLegalRoom(jrr.roomId) && _RHF.getRoomManager().getRoomState(jrr.roomId) == 0)
        status = JOIN_ROOM_STATUS;
    else status = JOIN_ROOM_ERROR;
    JoinRoomResponse jrre;
    jrre.status = status;
    buffer = JsonResponsePacketSerializer::serializeResponse(jrre);
    std::copy(buffer.begin(), buffer.end(), rr.buffer.begin());
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo ri)
{
    unsigned int status = 0;
    CreateRoomRequest crr = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(ri.buffer);
    vector<RoomData> roomData = _RHF.getRoomManager().getRooms();
    RoomData rd;
    for (auto it = roomData.begin(); it != roomData.end(); ++it)
    {
        if (it->name == crr.roomName && it->maxPlayers == crr.maxUsers &&
            it->numOfQuestionsInGame == crr.questionsCount && it->timePerQuestion == crr.answerTimeout)
        {
            status = CREATE_ROOM_STATUS;
            rd = *it;
            break;
        }
    }
    if (status != CREATE_ROOM_STATUS)
        status = CREATE_ROOM_ERROR;
    else _RHF.getRoomManager().createRoom(_user, rd);
    CreateRoomResponse crre;
    crre.status = status;
    rr.buffer = JsonResponsePacketSerializer::serializeResponse(crre);
    rr.newHandler = _RHF.createMenuRequestHandler(_user);
    return rr;
}