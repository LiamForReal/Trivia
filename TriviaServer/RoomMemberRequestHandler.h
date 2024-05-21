class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId, LoggedUser member);
	~RoomMemberRequestHandler();
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	RequestHandlerFactory& _rhf;
	unsigned int roomId;
	LoggedUser Member;
};

