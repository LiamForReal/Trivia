#include "LoginRequestHandler.h"
#include <iostream>

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (LOGIN_RC == requestInfo.id) || (SIGNUP_RC == requestInfo.id);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	std::vector<unsigned char> buffer;
	unsigned int status = 0;
	LoginManager lm = LoginManager();
	if (LOGIN_RC == requestInfo.id)
	{
		LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		status = lm.login(lr.username, lr.password);
		LoginResponse lresponse;
		lresponse.status = status;
		buffer = JsonResponsePacketSerializer::serializeResponse(lresponse);
	}
	else if (SIGNUP_RC == requestInfo.id)
	{
		SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		status = lm.singup(sr.username, sr.password, sr.email);
		SignupResponse sresponse;
		sresponse.status = status;
		buffer = JsonResponsePacketSerializer::serializeResponse(sresponse);
	}

	RequestResult rr = RequestResult();
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	rr.newHandler = nullptr; // should be the next handler that the user should pass
	return rr;
}