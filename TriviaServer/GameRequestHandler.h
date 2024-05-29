class RequestHandlerFactory;
#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "includes.hpp"
#include "defines.hpp"
#include "PlayerResults.hpp"
#include <random>

class GameRequestHandler : virtual public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory rhf, LoggedUser user, unsigned int roomId);
	~GameRequestHandler();
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& _rhf;
	LoggedUser _user;
	unsigned int _roomId;
	unsigned int questionId;
};

