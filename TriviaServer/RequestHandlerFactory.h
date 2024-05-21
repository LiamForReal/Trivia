class LoginRequestHandler;
class MenuRequestHandler;
#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	~RequestHandlerFactory();
	LoginRequestHandler* creatLoginRequestHandler();
	LoginManager& getLoginMeneger();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser loggedUser);
	RoomManager& getRoomManager() const;
	StatisticsManager& getStatisticsManager() const;
private:
	IDatabase* dataBace;
	LoginManager* loginMeneger;
	RoomManager* _roomManager;
	StatisticsManager* _statisticsManager;
};

