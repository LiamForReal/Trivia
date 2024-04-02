#include "MagshMessageServer.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>

// using static const instead of macros 
static const unsigned short PORT = 8878;
static const unsigned int IFACE = 0;

using std::string;
using std::mutex;
using std::unique_lock;
using std::vector;


MagshMessageServer::MagshMessageServer()
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception( __FUNCTION__ " - socket");
}

MagshMessageServer::~MagshMessageServer()
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

void MagshMessageServer::serve()
{
	bindAndListen();

	// create new thread for handling message
	std::thread tr(&MagshMessageServer::handleReceivedMessages, this);
	tr.detach();

	std::string input_string;
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		acceptClient();
		std::getline(std::cin, input_string);
		if (input_string == "EXIT")
			break;
	}
}


// listen to connecting requests from clients
// accept them, and create thread for each client
void MagshMessageServer::bindAndListen()
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

void MagshMessageServer::acceptClient()
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	// create new thread for client	and detach from it
	std::thread tr(&MagshMessageServer::clientHandler, this, client_socket);
	tr.detach();

}



void MagshMessageServer::clientHandler(const SOCKET client_socket)
{
	char* msg = new char[100];
	int bytesReceived = 1;
	while (bytesReceived != 0 && bytesReceived != -1)
	{
		Helper::sendData(client_socket, "Hello");
		bytesReceived = recv(client_socket, msg, 100, 0);
		if(strcmp(msg, "Hello") == 0)
			std::cout << "client enter: Hello\n";
	}
	closesocket(client_socket);
}

void MagshMessageServer::handleReceivedMessages(const char* msg, const SOCKET client_socket)
{
	if (strcmp("Hello", msg) == 0)
		Helper::sendData(client_socket, "Hello");
	else Helper::sendData(client_socket, "Enter Hello!");
}

//std::string MagshMessageServer::build_receive_message(const SOCKET client_socket, const int msg_code);