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
	unsigned int status = 0;
	if (LOGIN_RC == requestInfo.id)
	{
		LoginResponse lresponse = LoginResponse();
		LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		status = rhf.getLoginMeneger().login(lr.username, lr.password);
		lresponse.status = status;
		this->rr.buffer = JsonResponsePacketSerializer::serializeResponse(lresponse);
		if (status == LOGIN_STATUS)
			this->rr.newHandler = rhf.createMenuRequestHandler(LoggedUser(lr.username));
	}
	else if (SIGNUP_RC == requestInfo.id)
	{
		SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		status = rhf.getLoginMeneger().singup(sr.username, sr.password, sr.email);
		SignupResponse sresponse;
		sresponse.status = status;
		this->rr.buffer = JsonResponsePacketSerializer::serializeResponse(sresponse);
	}
	else throw std::runtime_error("invalid request id [login request handler]");
	if (this->rr.newHandler == nullptr)
		this->rr.newHandler = rhf.creatLoginRequestHandler();
	return this->rr;
}