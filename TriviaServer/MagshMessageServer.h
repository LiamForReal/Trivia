#pragma once

#include "MagshChat.h"
#include <deque>
#include <queue>
#include <mutex>
#include <map>
#include <condition_variable>
#include <WinSock2.h>
#include "RecvMessage.h"
#include "LoginRequestHandler.h"

// Q: why do we need this class ?
// A: this is the main class which holds all the resources,
// accept new clients and handle them.
class MagshMessageServer
{
public:
	MagshMessageServer();
	~MagshMessageServer();
	void serve();


private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(const SOCKET client_socket);
	void handleReceivedMessages(const char* msg, const SOCKET client_socket);
	//std::string build_receive_message(const SOCKET client_socket, const int msg_code);
	std::map<SOCKET, LoginRequestHandler> clients;

	SOCKET _socket;
	MagshChat _doc;

	// Queue for all clients. This way we will know who's the current writer.
	// SOCKET: client socket
	// string: userName
	std::deque<std::pair<SOCKET, std::string>> _clients;


	// Queue for messages - Will hold the mssage code and the file data. To add messages use std::ref<const ClientSocket>
	// SOCKET: client socket
	// string: message
	std::queue<RecvMessage*> _messageHandler;

	std::mutex _mtxReceivedMessages;
	std::condition_variable _msgQueueCondition;
};

