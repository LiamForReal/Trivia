class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameManager.h"
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
	GameRequestHandler* createGameRequestHandler(LoggedUser loggedUser, unsigned int roomId);
	LoginManager& getLoginMeneger();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser loggedUser);
	RoomManager& getRoomManager() const;
	GameManager& getGameManager() const;
	StatisticsManager& getStatisticsManager() const;
	
private:
	LoginManager* _loginMeneger;
	GameManager* _gameManager;
	RoomManager* _roomManager;
	StatisticsManager* _statisticsManager;
};

