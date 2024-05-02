#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
	this->dataBace = new SqliteDataBase();
	this->loginMeneger = LoginManager();
}

RequestHandlerFactory::~RequestHandlerFactory() {}

LoginRequestHandler RequestHandlerFactory::creatLoginRequestHandler()
{
	return LoginRequestHandler();
}
LoginManager& RequestHandlerFactory::getLoginMeneger()
{
	return loginMeneger;
}
/*
* MenuRequestHandler RequestHandlerFactory::createMenuRequestHandler()
{
	MenuRequestHandler mrh = MenuRequestHandler();
	return ;
}
*/
