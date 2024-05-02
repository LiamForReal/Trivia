#include "MenuRequestHandler.h"

RoomManager MenuRequestHandler::getRoomManager() const
{
	return _roomManager;
}

StatisticsManager MenuRequestHandler::getStatisticsManager() const
{
	return _statisticsManager;
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& ri)
{
	return ri.id >= 300 && ri.id <= 800;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::signout(RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo& ri)
{
	StatisticsManager sm = StatisticsManager();
	RequestResult rr = RequestResult();
	string playerStats = sm.getUserStatistics(_user.getUserName());
    unsigned char* tmp = new unsigned char[playerStats.length() + 1];
    std::copy(playerStats.begin(), playerStats.end(), tmp);
    tmp[playerStats.length()] = '\0';
	for (int i = 0; i < playerStats.length() + 1; i++)
		rr.buffer[i] = tmp[i];
	rr.newHandler = nullptr;
	return rr;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo& ri)
{
	StatisticsManager sm = StatisticsManager();
	RequestResult rr = RequestResult();
	vector<string> HighScores = sm.getHighScore();
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

RequestResult MenuRequestHandler::joinRoom(RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo& ri)
{
	RequestResult rr = RequestResult();
	return rr;
}