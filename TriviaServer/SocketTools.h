#pragma once

#include "FileWriter.h"
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "RecvMessage.h"
#include <map>
#include "LoginRequestHandler.h"
#include "Communicator.h"


// Q: why do we need this class ?
// A: this is the main class which holds all the resources,
// accept new clients and handle them.
class SocketTools
{
public:
	SocketTools();
	~SocketTools();
	void serve();


private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(const SOCKET client_socket);
	void checkifInput();

	Communicator _communicator;
	SOCKET _socket;

};

