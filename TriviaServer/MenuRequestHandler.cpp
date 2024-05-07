#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& rhf, LoggedUser user) : _RHF(rhf)
{
	this->_user = user;
}

MenuRequestHandler::~MenuRequestHandler() {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& ri)
{
	return ri.id >= 300 && ri.id <= 800;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& ri)
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

RequestResult MenuRequestHandler::signout(RequestInfo ri)
{
	std::vector<unsigned char> buffer;
	_RHF.getLoginMeneger().logout(_user.getUserName());
	RequestResult rr = RequestResult();
	rr.newHandler = new MenuRequestHandler(_RHF, _user); // should be the next handler that the user should pass
	return rr;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo ri)
{
	std::vector<unsigned char> buffer;
	RequestResult rr = RequestResult();
	rr.newHandler = new MenuRequestHandler(_RHF, _user); // should be the next handler that the user should pass
	if (_RHF.getRoomManager().getRooms().size() <= 0)
	{
		//error
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
	RequestResult rr = RequestResult();
	for (int i = 0; i < buffer.size(); i++)
	{
		rr.buffer[i] = buffer[i];
	}
	rr.newHandler = new MenuRequestHandler(_RHF, _user);
	return rr;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	string playerStats = _RHF.getStatisticsManager().getUserStatistics(_user.getUserName());
	unsigned char* tmp = new unsigned char[playerStats.size() + 1];
	std::copy(playerStats.begin(), playerStats.end(), tmp);
	tmp[playerStats.size()] = '\0';
	std::copy(rr.buffer.begin(), rr.buffer.end(), tmp);
	rr.newHandler = new MenuRequestHandler(_RHF, _user);
	return rr;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo ri)
{
	RequestResult rr = RequestResult();
	vector<string> HighScores = _RHF.getStatisticsManager().getHighScore();
	int i = 0, size = 0, j = 0;
	rr.newHandler = new MenuRequestHandler(_RHF, _user);
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
		for (j = 0 ; j < HighScores[i].size() ;j ++)
		{
			HighScores[i][j] = tmp[j];
		}
		tmp += '|';
	}

	unsigned char* tmp2 = new unsigned char[tmp.size() + 1];
	tmp2[tmp.size()] = '\0';
	std::copy(rr.buffer.begin(), rr.buffer.end(), tmp2);
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
	RequestResult rr = RequestResult();
	for (int i = 0; i < buffer.size(); i++)
	{
		rr.buffer[i] = buffer[i];
	}
	rr.newHandler = new MenuRequestHandler(_RHF, _user);
	return rr;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo ri)
{
	std::vector<unsigned char> buffer;
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
	buffer = JsonResponsePacketSerializer::serializeResponse(crre);
	RequestResult rr = RequestResult();
	for (int i = 0; i < buffer.size(); i++)
	{
		rr.buffer[i] = buffer[i];
	}
	rr.newHandler = new MenuRequestHandler(_RHF, _user);
	return rr;
}