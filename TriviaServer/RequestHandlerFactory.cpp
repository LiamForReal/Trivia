#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() 
{
	this->dataBace = new SqliteDataBase();
	this->loginMeneger = new LoginManager();
	this->_roomManager = new RoomManager();
	this->_statisticsManager = new StatisticsManager();
}

RequestHandlerFactory::~RequestHandlerFactory() {}
//{
//	delete this->_statisticsManager;
//	delete this->_roomManager;
//	delete this->loginMeneger;
//	this->dataBace->close();
//	delete this->dataBace;
//}

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


MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser loggedUser)
{
	return new MenuRequestHandler(*this, loggedUser);
}
