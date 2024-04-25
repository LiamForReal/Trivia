#include "Communicator.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <vector>
#include "defines.hpp"

void Communicator::handleNewClient(SOCKET clientSocket)
{
    std::string clientMsg = "";
    unsigned int statusCode = 0;
    unsigned int clientMsgLength = 0;
    size_t i = 0;
    int j = 0;

    LoginRequestHandler lrh;
    RequestInfo ri = RequestInfo();
    RequestResult rr;
    ri.id = 0;

    statusCode = (unsigned int)Helper::getStatusCodeFromSocket(clientSocket);

    std::cout << "DEBUG: Status code: " << statusCode << std::endl;
    ri.buffer.insert(ri.buffer.begin(), STATUS_CODE_BYTES_LENGTH, static_cast<unsigned char>(statusCode));

    clientMsgLength = Helper::getLengthPartFromSocket(clientSocket);

    std::cout << "DEBUG: Length: " << clientMsgLength << std::endl;
    // Insert message length in little-endian format
    for (j = 0; j < BYTES_TO_COPY; ++j) {
        ri.buffer.insert(ri.buffer.begin() + INC + j, static_cast<unsigned char>((clientMsgLength >> (8 * j)) & 0xFF));
    }

    clientMsg = Helper::getStringPartFromSocket(clientSocket, clientMsgLength);
    clientMsg[clientMsgLength] = '\0';

    for (i = 0; i < clientMsgLength; i++)
    {
        ri.buffer.push_back(static_cast<unsigned char>(clientMsg[i]));
    }

    std::cout << "DEBUG: The message is: " << clientMsg << std::endl;


    ri.id = statusCode;
    ri.recievalTime = time(nullptr);
    try
    {
        if (lrh.isRequestRelevant(ri))
        {
            rr = lrh.handleRequest(ri);
            Helper::sendVector(clientSocket, rr.buffer);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    ri.buffer.clear();

    closesocket(clientSocket);
}