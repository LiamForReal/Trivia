#pragma once
#include "includes.hpp"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	~MenuRequestHandler();
	bool isRequestRelevant(const RequestInfo& ri) override;
	RequestResult handleRequest(const RequestInfo& ri) override;
	RequestResult signout(RequestInfo ri);
	RequestResult getRooms(RequestInfo ri);
	RequestResult getPlayersInRoom(RequestInfo ri);
	RequestResult getPersonalStats(RequestInfo& ri);
	RequestResult getHighScore(RequestInfo ri);
	RequestResult joinRoom(RequestInfo ri);
	RequestResult createRoom(RequestInfo ri);

private:
	LoggedUser _user;
	RoomManager _roomManager;
	StatisticsManager _statisticsManager;
	RequestHandlerFactory _requestHandlerFactory;
};

