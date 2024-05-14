#include "LoginRequestHandler.h"
#include <iostream>

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& newRhf) : rhf(newRhf) 
{
	this->rr = RequestResult();
}

LoginRequestHandler::~LoginRequestHandler() {}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (LOGIN_RC == requestInfo.id) || (SIGNUP_RC == requestInfo.id);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	if (!this->rr.buffer.empty())
	{
		this->rr.buffer.clear();
	}

	std::vector<unsigned char> buffer = std::vector<unsigned char>();
	unsigned int status = 0;
	string username = "";

	if (LOGIN_RC == requestInfo.id)
	{
		LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		status = rhf.getLoginMeneger().login(lr.username, lr.password);
		std::cout << "DEBUG: STATUS " << status << std::endl;
		LoginResponse lresponse;
		lresponse.status = status;
		buffer = JsonResponsePacketSerializer::serializeResponse(lresponse);
		username = lr.username;
		this->rr.newHandler = rhf.createMenuRequestHandler(LoggedUser(username));
	}
	else if (SIGNUP_RC == requestInfo.id)
	{
		SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		status = rhf.getLoginMeneger().singup(sr.username, sr.password, sr.email);
		SignupResponse sresponse;
		sresponse.status = status;
		buffer = JsonResponsePacketSerializer::serializeResponse(sresponse);
		username = sr.username;
	}
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(this->rr.buffer));
	buffer.clear();

	return this->rr;
}