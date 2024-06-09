#include "SocketTools.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>

#define AMOUNT_OF_BYTES 5
// using static const instead of macros 
static const unsigned short PORT = 8888;
static const unsigned int IFACE = 0;

using std::string;
using std::vector;


SocketTools::SocketTools()
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

SocketTools::~SocketTools()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_socket);
	}
	catch (...) {}
}

void SocketTools::serve()
{
	bindAndListen();
	std::string input_string;
	std::thread tr(&SocketTools::checkifInput, this);
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		acceptClient();

	}
}


// listen to connecting requests from clients
// accept them, and create thread for each client
void SocketTools::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");

}

void SocketTools::checkifInput()
{
	string input_string;
	while (true)
	{
		std::getline(std::cin, input_string);
		if (input_string == "EXIT")
		{
			std::map<SOCKET, IRequestHandler*> handlers = this->_communicator.getHandlers();
			for (auto it = handlers.begin(); it != handlers.end(); ++it)
			{
				closesocket(it->first);
				delete it->second;
			}
			exit(1);
		}
	}

}

void SocketTools::acceptClient()
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	std::thread tr(&SocketTools::clientHandler, this, client_socket);
	tr.detach();

}

void SocketTools::clientHandler(const SOCKET client_socket)
{
	this->_communicator.handleNewClient(client_socket);
}