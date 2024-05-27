#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() 
{
	this->loginMeneger = new LoginManager();
	this->_roomManager = new RoomManager();
	this->_statisticsManager = new StatisticsManager();
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete this->_statisticsManager;
	delete this->_roomManager;
	delete this->loginMeneger;
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
	return *loginMeneger;
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
