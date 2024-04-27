#pragma once
#include "includes.hpp"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler
{
public:

private:
	LoggedUser _user;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
	RequestHandlerFactory& _requestHandleFuctory;
};

