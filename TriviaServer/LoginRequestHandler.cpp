#include "LoginRequestHandler.h"
#include <iostream>

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& newRhf) : rhf(newRhf) {}

LoginRequestHandler::~LoginRequestHandler() {}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (LOGIN_RC == requestInfo.id) || (SIGNUP_RC == requestInfo.id);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	std::vector<unsigned char> buffer;
	unsigned int status = 0;
	RequestResult rr = RequestResult();
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
	//std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));

	rr.buffer = std::vector<unsigned char>();
	for (int i = 0; i < buffer.size(); i++)
	{
		rr.buffer.push_back(buffer[i]);
	}

	rr.newHandler = rhf.createMenuRequestHandler(LoggedUser(username));

	std::cout << "DEBUG: BUFFER ";
	for (int i = 0; i < rr.buffer.size(); i++)
	{
		std::cout << rr.buffer[i];
	}
	std::cout << std::endl; // suka blyat
	return rr;
}