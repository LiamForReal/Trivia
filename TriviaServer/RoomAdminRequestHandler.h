class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

/**
* The RoomAdminRequestHandler inherits from IRequestHandler which is the base class for all Handlers.
* 
* The RoomAdminRequestHandler is created more than once, during a creation of room.
* Only the user who creates a room gets this manager.
* 
* It advances to the next RequestHandler in two ways:
* 1. when it successfully closes the room for all the users it advances to MenuRequestHandler.
* or
* 2. when the owner starts the game successfully the user advances to GameRequestHandler.
*/

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

