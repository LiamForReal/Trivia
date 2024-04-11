#pragma once
#include "IRequestHandler.h"
#include "Responses.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

class LoginRequestHandler : virtual public IRequestHandler
{
	public:
		static bool isRequestRelevant(const RequestInfo& requestInfo);
		static RequestResult handleRequest(const RequestInfo& requestInfo);
};

