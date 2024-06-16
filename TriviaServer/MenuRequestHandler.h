class RequestHandlerFactory;
#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Question.h"

/**
* The MenuRequestHandler inherits from IRequestHandler which is the base class for all Handlers.
*
* The MenuRequestHandler is created more than once, created after a successful login.
* It gives access to the user to call the functionality of the buttons in the menu of the Trivia.
* 
* It advances to the next RequestHandler in two ways:
* 1. when the user creates a room successfully the user advances to RoomAdminRequestHandler.
* or
* 2. when the user joins a room successfully the user advances to RoomMemberRequestHandler.
*/

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& rhf, LoggedUser user);
	~MenuRequestHandler();
	bool isRequestRelevant(const RequestInfo& ri) override;
	RequestResult handleRequest(const RequestInfo& ri) override;
	RequestResult signout(RequestInfo ri);
	RequestResult getRooms(RequestInfo ri);
	RequestResult getPlayersInRoom(RequestInfo ri);
	RequestResult getPersonalStats(RequestInfo ri);
	RequestResult getHighScore(RequestInfo ri);
	RequestResult joinRoom(RequestInfo ri);
	RequestResult createRoom(RequestInfo ri);
	RequestResult addNewQuestion(RequestInfo ri);
	RequestResult matchMake(RequestInfo ri);
private:
	LoggedUser _user;
	RequestHandlerFactory& _RHF;
	RequestResult rr;
};