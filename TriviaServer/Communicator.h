#pragma once
#include <WinSock2.h>
#include "IRequestHandler.h"
#include "includes.hpp"
#include "RequestHandlerFactory.h"

class Communicator
{
	public:
		Communicator();
		~Communicator();
		void handleNewClient(SOCKET clientSocket);
		RequestInfo buildRI(SOCKET clientSocket, unsigned int statusCode);

	private:
		std::map<SOCKET, IRequestHandler*> _handlers;
		RequestHandlerFactory* rhf;
};

