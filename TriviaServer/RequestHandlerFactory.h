#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	LoginRequestHandler creatLoginRequestHandler();
	LoginManager& getLoginMeneger();
	MenuRequestHandler createMenuRequestHandler();
	RoomManager getRoomManager() const;
	StatisticsManager getStatisticsManager() const;
private:
	IDatabase* dataBace;
	LoginManager loginMeneger;
	RoomManager _roomManager;
	StatisticsManager _statisticsManager;
};

