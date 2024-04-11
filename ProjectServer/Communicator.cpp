#include "Communicator.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <vector>

#define MAX_AMOUNT_OF_BYTES 8000
#define INIT_VEC_SIZE 5
#define BYTES_TO_COPY 4
#define INC 1

void Communicator::handleNewClient(SOCKET clientSocket)
{
	char* msg = new char[MAX_AMOUNT_OF_BYTES];
	int msgLen = 1;
	std::string clientMsg = "";
	std::string stringClientMsgLength = "";
	unsigned int statusCode = 0, lenght = 0;

	unsigned int clientMsgLength = 0;
	size_t i = 0;

	RequestInfo ri = RequestInfo();
	RequestResult rr;
	ri.id = 0;

	while (true)
	{
		statusCode = 0;
		clientMsg = "";
		stringClientMsgLength = "";
		clientMsgLength = 0;

		statusCode = (unsigned int)Helper::getUnsignedIntPartFromSocket(clientSocket, 1);

		std::cout << "Status code: " << statusCode << std::endl;
		ri.buffer.push_back(statusCode);

		//stringClientMsgLength = Helper::getStringPartFromSocket(clientSocket, 4);

		//for (i = 0; i < stringClientMsgLength.size(); i++)
		//{
		//	ri.buffer.push_back(stringClientMsgLength[i]);
		//}

		//std::memcpy(&clientMsgLength, ri.buffer.data() + INC, BYTES_TO_COPY);
		clientMsgLength = Helper::getLengthPartFromSocket(clientSocket, 4);

		std::cout << "Length: " << clientMsgLength << std::endl;

		clientMsg = Helper::getStringPartFromSocket(clientSocket, clientMsgLength);
		clientMsg[clientMsgLength] = '\0';

		std::cout << "The message is: " << clientMsg << std::endl;

		//for (i = 0; i < clientMsgLength; i++)
		//{
		//	ri.buffer.push_back(clientMsg[i]);
		//}

		ri.id = ri.buffer[0];
		ri.recievalTime = time(nullptr);


		//if (LoginRequestHandler::isRequestRelevant(ri))
		//{
		//	rr = LoginRequestHandler::handleRequest(ri);
		//	Helper::sendVector(clientSocket, rr.buffer);
		//}

		ri.buffer.clear();

		break;
	}

	closesocket(clientSocket);
}