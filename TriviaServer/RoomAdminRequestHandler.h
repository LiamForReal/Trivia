class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "includes.hpp"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId);
	~RoomAdminRequestHandler();
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& _rhf;
	unsigned int roomId;
};

