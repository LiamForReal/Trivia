#include "RequestHandlerFactory.h"

LoginRequestHandler RequestHandlerFactory::creatLoginRequestHandler()
{
	return LoginRequestHandler();
}
LoginManager& RequestHandlerFactory::getLoginMeneger()
{
	return loginMeneger;
}