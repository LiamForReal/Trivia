#pragma once
#include <WinSock2.h>
#include "IRequestHandler.h"

class Communicator
{
	public:
		void handleNewClient(SOCKET clientSocket);


	private:
		// TODO in future versions...
};

