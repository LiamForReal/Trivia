#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	~RequestHandlerFactory();
	LoginRequestHandler creatLoginRequestHandler();
	LoginManager& getLoginMeneger();
	//MenuRequestHandler createMenuRequestHandler();
private:
	IDatabase* dataBace;
	LoginManager loginMeneger;
};

