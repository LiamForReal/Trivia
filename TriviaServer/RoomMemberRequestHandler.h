class RequestHandlerFactory;
#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

/**
* The RoomMemberRequestHandler inherits from IRequestHandler which is the base class for all Handlers.
*
* The RoomMemberRequestHandler is created more than once, during a join to a room.
* Only the users who join to a room get this manager.
* 
* It advances to the next RequestHandler in two ways:
* 1. when the user successfully leaves the room the user advances to MenuRequestHandler.
* or
* 2. when the owner of the room starts the game successfully the user advances to GameRequestHandler.
*/

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

