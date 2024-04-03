#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : virtual public IRequestHandler
{
	public:
		bool isRequestRelevant(const RequestInfo& requestInfo);
		RequestResult handleRequest(const RequestInfo& requestInfo);
};

