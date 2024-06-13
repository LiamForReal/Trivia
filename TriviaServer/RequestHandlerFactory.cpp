#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() 
{
	this->_loginMeneger = new LoginManager();
	this->_roomManager = new RoomManager();
	this->_gameManager = new GameManager();
	this->_statisticsManager = new StatisticsManager();
	this->_db = new SqliteDataBase();
	if (!this->_db->open())
		throw std::runtime_error("Failed to open database!");
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete this->_loginMeneger;
	delete this->_roomManager;
	delete this->_gameManager;
	delete this->_statisticsManager;
	delete this->_db;
}

RoomManager& RequestHandlerFactory::getRoomManager() const
{
	return *this->_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager() const
{
	return *this->_statisticsManager;
}

LoginRequestHandler* RequestHandlerFactory::creatLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginMeneger()
{
	return *_loginMeneger;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(unsigned int roomId, LoggedUser loggedUser)
{
	return new RoomAdminRequestHandler(*this, roomId, loggedUser);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(unsigned int roomId, LoggedUser loggedUser)
{
	return new RoomMemberRequestHandler(*this, roomId, loggedUser);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser loggedUser)
{
	return new MenuRequestHandler(*this, loggedUser);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser loggedUser, unsigned int roomId)
{
	return new GameRequestHandler(*this, loggedUser, roomId);
}

GameManager& RequestHandlerFactory::getGameManager() const
{
	return *_gameManager;
}
