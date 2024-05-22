class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomManager.h"
#include "includes.hpp"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	~RequestHandlerFactory();
	LoginRequestHandler* creatLoginRequestHandler();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(unsigned int roomId, LoggedUser loggedUser);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(unsigned int roomId, LoggedUser loggedUser);
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

