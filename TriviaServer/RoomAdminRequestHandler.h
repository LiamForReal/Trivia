class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId, LoggedUser owner);
	~RoomAdminRequestHandler();
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& _rhf;
	unsigned int roomId;
	LoggedUser Owner;
};

