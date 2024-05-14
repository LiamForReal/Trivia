class RequestHandlerFactory;
#pragma once
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"


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
	RequestResult getPersonalStats(RequestInfo& ri);
	RequestResult getHighScore(RequestInfo ri);
	RequestResult joinRoom(RequestInfo ri);
	RequestResult createRoom(RequestInfo ri);

private:
	LoggedUser _user;
	RequestHandlerFactory& _RHF;
	RequestResult rr;
};