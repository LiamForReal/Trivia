#include "LoginRequestHandler.h"
#include <iostream>

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (LOGIN_RC == requestInfo.id) || (SIGNUP_RC == requestInfo.id);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	std::vector<unsigned char> buffer;

	if (LOGIN_RC == requestInfo.id)
	{
		LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		std::cout << "DEBUG: Logins client... Username: " << lr.username << ", Password: " << lr.password << std::endl;
		LoginResponse lresponse;
		lresponse.status = LOGIN_STATUS;

		buffer = JsonResponsePacketSerializer::serializeResponse(lresponse);
	}
	else if (SIGNUP_RC == requestInfo.id)
	{
		SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		std::cout << "DEBUG: Sign Ups client... Username: " << sr.username << ", Password: " << sr.password << ", Email: " << sr.email << std::endl;
		SignupResponse sresponse;
		sresponse.status = SIGNUP_STATUS;

		buffer = JsonResponsePacketSerializer::serializeResponse(sresponse);
	}

	RequestResult rr = RequestResult();
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	rr.newHandler = nullptr; // should be the next handler that the user should pass
	return rr;
}