#pragma once
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler creatLoginRequestHandler();
	LoginManager& getLoginMeneger();

private:
	IDatabase* dataBace;
	LoginManager loginMeneger;
};

