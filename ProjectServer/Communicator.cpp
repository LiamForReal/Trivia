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
    std::string clientMsg = "";
    unsigned int statusCode = 0;
    unsigned int clientMsgLength = 0;
    size_t i = 0;

    RequestInfo ri = RequestInfo();
    RequestResult rr;
    ri.id = 0;
    // ri.buffer.resize(1 + 4);

    statusCode = (unsigned int)Helper::getStatusCodeFromSocket(clientSocket);

    std::cout << "DEBUG: Status code: " << statusCode << std::endl;
    // ri.buffer.push_back(statusCode);
    ri.buffer.insert(ri.buffer.begin(), 1, static_cast<unsigned char>(statusCode));

    clientMsgLength = Helper::getLengthPartFromSocket(clientSocket);

    std::cout << "DEBUG: Length: " << clientMsgLength << std::endl;
    // Insert message length in little-endian format
    for (int j = 0; j < BYTES_TO_COPY; ++j) {
        ri.buffer.insert(ri.buffer.begin() + INC + j, static_cast<unsigned char>((clientMsgLength >> (8 * j)) & 0xFF));
    }

    clientMsg = Helper::getStringPartFromSocket(clientSocket, clientMsgLength);
    clientMsg[clientMsgLength] = '\0';

    // ri.buffer.resize(1 + 4 + clientMsgLength);

    // std::memcpy(ri.buffer.data() + INC + BYTES_TO_COPY, clientMsg.data(), clientMsgLength);

    for (i = 0; i < clientMsgLength; i++)
    {
        ri.buffer.push_back(static_cast<unsigned char>(clientMsg[i]));
    }

    std::cout << "DEBUG: The message is: " << clientMsg << std::endl;

    std::cout << "DEBUG: DATA => " << ri.buffer.data() << std::endl;

    ri.id = statusCode;
    ri.recievalTime = time(nullptr);

    try
    {
        if (LoginRequestHandler::isRequestRelevant(ri))
        {
            rr = LoginRequestHandler::handleRequest(ri);
            // std::cout << rr.buffer.data() << std::endl;
            Helper::sendVector(clientSocket, rr.buffer);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    ri.buffer.clear();

    closesocket(clientSocket);
}


// 
//void Communicator::handleNewClient(SOCKET clientSocket)
//{
//	std::string clientMsg = "";
//	unsigned int statusCode = 0;
//	unsigned int clientMsgLength = 0;
//	size_t i = 0;
//
//	RequestInfo ri = RequestInfo();
//	RequestResult rr;
//	ri.id = 0;
//	//ri.buffer.resize(1 + 4);
//
//	statusCode = (unsigned int)Helper::getStatusCodeFromSocket(clientSocket);
//
//	std::cout << "DEBUG: Status code: " << statusCode << std::endl;
//	//ri.buffer.push_back(statusCode);
//	ri.buffer.insert(ri.buffer.begin(), 1, statusCode);
//
//
//	clientMsgLength = Helper::getLengthPartFromSocket(clientSocket);
//
//	std::cout << "DEBUG: Length: " << clientMsgLength << std::endl;
//	//std::memcpy(ri.buffer.data() + INC, &clientMsgLength, BYTES_TO_COPY);
//	ri.buffer.insert(ri.buffer.begin() + 1, 4, clientMsgLength);
//
//
//	clientMsg = Helper::getStringPartFromSocket(clientSocket, clientMsgLength);
//	clientMsg[clientMsgLength] = '\0';
//
//	//ri.buffer.resize(1 + 4 + clientMsgLength);
//
//	//std::memcpy(ri.buffer.data() + INC + BYTES_TO_COPY, clientMsg.data(), clientMsgLength);
//
//	for (i = 0; i < clientMsgLength; i++)
//	{
//		ri.buffer.push_back(static_cast<unsigned char>(clientMsg[i]));
//	}
//
//	std::cout << "DEBUG: The message is: " << clientMsg << std::endl;
//
//	//std::cout << "DEBUG: DATA => " << ri.buffer.data() << std::endl;
//
//	ri.id = statusCode;
//	ri.recievalTime = time(nullptr);
//
//	try
//	{
//		if (LoginRequestHandler::isRequestRelevant(ri))
//		{
//			rr = LoginRequestHandler::handleRequest(ri);
//			std::cout << rr.buffer.data() << std::endl;
//			Helper::sendVector(clientSocket, rr.buffer);
//		}
//	}
//	catch (const std::exception& e)
//	{
//		std::cout << e.what() << std::endl;
//	}
//
//	ri.buffer.clear();
//
//	closesocket(clientSocket);
//}