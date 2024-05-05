#include "RequestHandlerFactory.h"

RoomManager RequestHandlerFactory::getRoomManager() const
{
	return this->_roomManager;
}

StatisticsManager RequestHandlerFactory::getStatisticsManager() const
{
	return this->_statisticsManager;
}

LoginRequestHandler RequestHandlerFactory::creatLoginRequestHandler()
{
	return LoginRequestHandler();
}
LoginManager& RequestHandlerFactory::getLoginMeneger()
{
	return loginMeneger;
}


MenuRequestHandler RequestHandlerFactory::createMenuRequestHandler()
{
	MenuRequestHandler mrh =  MenuRequestHandler();
	return mrh;
}
