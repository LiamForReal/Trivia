#include "MenuRequestHandler.h"

RoomManager MenuRequestHandler::getRoomManager() const //done
{
	return _roomManager;
}

StatisticsManager MenuRequestHandler::getStatisticsManager() const //done
{
	return _statisticsManager;
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& ri) //done
{
	return ri.id >= 300 && ri.id <= 800;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& ri) //done
{
	RequestResult rr = RequestResult();
	switch (ri.id)
	{
	case LOGOUT_RC:
		rr = signout(ri);
		break;
	case GET_ROOMS_RC:
		rr = getRooms(ri);
		break;
	case GET_PLAYERS_IN_ROOM_RC:
		rr = getPlayersInRoom(ri);
		break;
	case JOIN_ROOM_RC:
		rr = joinRoom(ri);
		break;
	case CREATE_ROOM_RC:
		rr = createRoom(ri);
		break;
	case GET_HIGH_SCORE_RC:
		rr = getHighScore(ri);
		break;
	}
	return rr;
}

RequestResult MenuRequestHandler::signout(RequestInfo ri) //why
{
	//std::vector<unsigned char> buffer;
	//unsigned int status = 0;
	//status = _requestHandlerFactory.getLoginMeneger().logout(_user.getUserName());
	//RequestResult rr = RequestResult();
	//rr.status = status;
	//buffer = JsonResponsePacketSerializer::serializeResponse(sresponse);
	//std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	//rr.newHandler = nullptr; // should be the next handler that the user should pass
	//return rr;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo ri) //why
{
	//std::vector<unsigned char> buffer;
	//unsigned int status = 0;
	//if (_roomManager.getRooms().size() > 0)
	//	status = GET_ROOMS_STATUS;
	//else status = GET_ROOMS_ERROR;
	//SignupResponse sresponse;
	//sresponse.status = status;
	//buffer = JsonResponsePacketSerializer::serializeResponse(sresponse);
	//RequestResult rr = RequestResult();
	//std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	//rr.newHandler = nullptr; // should be the next handler that the user should pass
	//return rr;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo ri) //done
{
	std::vector<unsigned char> buffer;
	unsigned int status = 0;
	GetPlayersInRoomRequest gpr = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(ri.buffer);
	Room room = _roomManager.getRoom(gpr.roomId);
	if (_roomManager.isLegalRoom(gpr.roomId)/* && _roomManager.getRoomState(jrr.roomId) != */)
		status = GET_PLAYERS_IN_ROOM_STATUS;
	else status = GET_PLAYERS_IN_ROOM_ERROR;
	GetPlayersInRoomResponse gpre;
	gpre.status = status;
	gpre.players = room.getAllUsers();
	buffer = JsonResponsePacketSerializer::serializeResponse(gpre);
	RequestResult rr = RequestResult();
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	rr.newHandler = nullptr;
}

//RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& ri) un needed for now
//{
//	RequestResult rr = RequestResult();
//	string playerStats = _statisticsManager.getUserStatistics(_user.getUserName());
//    unsigned char* tmp = new unsigned char[playerStats.length() + 1];
//    std::copy(playerStats.begin(), playerStats.end(), tmp);
//    tmp[playerStats.length()] = '\0';
//	for (int i = 0; i < playerStats.length() + 1; i++)
//		rr.buffer[i] = tmp[i];
//	rr.newHandler = nullptr;
//	return rr;
//}

RequestResult MenuRequestHandler::getHighScore(RequestInfo ri) //why
{
	RequestResult rr = RequestResult();
	vector<string> HighScores = _statisticsManager.getHighScore();
	int i = 0, size = 0;

	for (i = 0; i < HighScores.size(); i++)
		size += HighScores[i].length();

	unsigned char* tmp = new unsigned char[size + 1];

	for (i = 0; i < HighScores.size(); i++)
	{
		std::copy(HighScores[i].begin(), HighScores[i].end(), tmp);
		tmp += '|';
	}
	tmp[HighScores.size()] = '\0';
	for (i = 0; i < size + 1; i++)
		rr.buffer[i] = tmp[i];
	rr.newHandler = nullptr;
	return rr;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo ri) //done
{
	std::vector<unsigned char> buffer;
	unsigned int status = 0;
	JoinRoomRequest jrr = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(ri.buffer);
	Room room = _roomManager.getRoom(jrr.roomId);
	if (_roomManager.isLegalRoom(jrr.roomId)/* && _roomManager.getRoomState(jrr.roomId) != */ )
		status = JOIN_ROOM_STATUS;
	else status = JOIN_ROOM_ERROR;
	JoinRoomResponse jrre;
	jrre.status = status;
	buffer = JsonResponsePacketSerializer::serializeResponse(jrre);
	RequestResult rr = RequestResult();
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	rr.newHandler = nullptr;
	return rr;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo ri) // done
{
	std::vector<unsigned char> buffer;
	unsigned int status = 0;
	CreateRoomRequest crr = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(ri.buffer);
	vector<RoomData> roomData = _roomManager.getRooms();
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
	else _roomManager.createRoom(_user, rd);
	CreateRoomResponse crre;
	crre.status = status;
	buffer = JsonResponsePacketSerializer::serializeResponse(crre);
	RequestResult rr = RequestResult();
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	rr.newHandler = nullptr;
	return rr;
}