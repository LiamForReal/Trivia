class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

/**
* The LoginRequestHandler inherits from IRequestHandler which is the base class for all Handlers.
*
* The LoginRequestHandler is created more than once, created in the beginning of the user connection to the server,
* and advances to MenuRequestHandler for further functionality after successful login.
* It gives access to the user to login or signup to the Trivia.
*/

class LoginRequestHandler : virtual public IRequestHandler
{
	public:
		LoginRequestHandler(RequestHandlerFactory& newRhf);
		~LoginRequestHandler();
		bool isRequestRelevant(const RequestInfo& requestInfo) override;
		RequestResult handleRequest(const RequestInfo& requestInfo) override;
	private:
		RequestHandlerFactory& rhf;
		RequestResult rr;
};

