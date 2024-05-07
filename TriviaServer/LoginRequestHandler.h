class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "Responses.hpp"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class LoginRequestHandler : virtual public IRequestHandler
{
	public:
		LoginRequestHandler(RequestHandlerFactory& newRhf);
		~LoginRequestHandler();
		bool isRequestRelevant(const RequestInfo& requestInfo) override;
		RequestResult handleRequest(const RequestInfo& requestInfo) override;
	private:
		RequestHandlerFactory& rhf;
};

