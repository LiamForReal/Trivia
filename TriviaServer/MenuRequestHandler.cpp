#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(RequestInfo)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::signout(RequestInfo)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo)
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

RequestResult MenuRequestHandler::getHighScore(RequestInfo)
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

RequestResult MenuRequestHandler::joinRoom(RequestInfo)
{
	RequestResult rr = RequestResult();
	return rr;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo)
{
	RequestResult rr = RequestResult();
	return rr;
}