#pragma once
#include "includes.hpp"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);
	RequestResult getHighScore(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);

private:
	LoggedUser _user;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
	RequestHandlerFactory& _requestHandleFuctory;
};

