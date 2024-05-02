#pragma once
#include "includes.hpp"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(const RequestInfo& ri) override;
	RoomManager getRoomManager() const;
	StatisticsManager getStatisticsManager() const;
	RequestResult handleRequest(const RequestInfo& ri) override;
	RequestResult signout(RequestInfo& ri);
	RequestResult getRooms(RequestInfo& ri);
	RequestResult getPlayersInRoom(RequestInfo& ri);
	RequestResult getPersonalStats(RequestInfo& ri);
	RequestResult getHighScore(RequestInfo& ri);
	RequestResult joinRoom(RequestInfo& ri);
	RequestResult createRoom(RequestInfo& ri);

private:
	LoggedUser _user;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
};

