#include "LoginRequestHandler.h"
#include <iostream>

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return requestInfo.id == LOGIN_RC;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);

	LoginResponse lresponse;
	lresponse.status = LOGIN_STATUS;
	std::vector<unsigned char> buffer = JsonResponsePacketSerializer::serializeResponse(lresponse);

	std::cout << "DEBUG: Logins client... Username: " << lr.username << ", Password: " << lr.password << std::endl;

	RequestResult rr = RequestResult();
	std::copy(buffer.begin(), buffer.end(), std::back_inserter(rr.buffer));
	rr.newHandler = nullptr; // should be other handler when added (?)
	return rr;
}