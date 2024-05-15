#include "Communicator.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <vector>
#include "defines.hpp"
#include "MenuRequestHandler.h"
#include <mutex>

std::mutex mtx;

Communicator::Communicator()
{
    this->rhf = RequestHandlerFactory();
}

Communicator::~Communicator() {}

void Communicator::handleNewClient(SOCKET clientSocket)
{
    unsigned int statusCode = 0, size = 0;
    RequestInfo ri = RequestInfo();
    RequestResult rr = RequestResult();
    LoggedUser loggedUser = LoggedUser();
    mtx.lock();
    _handlers[clientSocket] = rhf.creatLoginRequestHandler();
    mtx.unlock(); 
    rr.newHandler = _handlers[clientSocket];

    try
    {
        mtx.lock();
        size = rhf.getLoginMeneger().getLoggedUsers().size();
        mtx.unlock();
        while (true)
        {
            if (loggedUser.getUserName() == "")
            {
                std::cout << "login again\n";
                do
                {
                    statusCode = Helper::socketHasData(clientSocket);
                    if (statusCode != 0 && statusCode != -1)
                    {
                        std::cout << "LOGIN REQUEST HANDLER\n\n";
                        ri = buildRI(clientSocket, statusCode);
                        std::cout << "DEBUG REQUEST CODE: " << ri.id << std::endl;
                        rr = rr.newHandler->handleRequest(ri);
                        if (rr.newHandler == nullptr)
                            rr.newHandler = _handlers[clientSocket];
                        else _handlers[clientSocket] = rr.newHandler;
                        Helper::sendVector(clientSocket, std::ref(rr.buffer));
                        std::cout << "DEBUG RESPONSE CODE: " << (unsigned int)rr.buffer[0] << std::endl;
                    }
                } while (rhf.getLoginMeneger().getLoggedUsers().size() == size);
                loggedUser = LoggedUser(JsonRequestPacketDeserializer::deserializeLoginRequest(ri.buffer).username);
                std::cout << "DEBUG: user login: " << loggedUser.getUserName() << std::endl;
            }
            
            do
            {
                statusCode = Helper::socketHasData(clientSocket);
                if (statusCode != 0 && statusCode != -1)
                {
                    std::cout << "MENU REQUEST HANDLER\n\n";
                    ri = buildRI(clientSocket, statusCode);
                    mtx.lock();
                    rr = _handlers[clientSocket]->handleRequest(ri);
                    mtx.unlock();
                    Helper::sendVector(clientSocket, rr.buffer);
                    std::cout << "after sending";
                    if ((unsigned int)rr.buffer[0] == LOGOUT_STATUS)
                    {
                        std::cout << "DEBUG: user logout: " << loggedUser.getUserName();
                        _handlers[clientSocket] = rr.newHandler;
                        loggedUser.setUserName("");
                    }
                }
            } while (rr.newHandler->isRequestRelevant(ri));
        }

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        ri.id = LOGOUT_RC;
        ri.buffer.clear();
        _handlers[clientSocket]->handleRequest(ri);
        std::cout << "client - " << clientSocket << " crashed!";
    }
    ri.buffer.clear();
    closesocket(clientSocket);
}

RequestInfo Communicator::buildRI(SOCKET clientSocket, unsigned int statusCode)
{
    RequestInfo ri = RequestInfo();
    ri.buffer = std::vector<unsigned char>();
    std::string clientMsg = "";
    unsigned int clientMsgLength = 0;
    size_t i = 0;
    int j = 0;

    ri.id = statusCode;

    std::cout << "DEBUG: Status code: " << statusCode << std::endl;
    ri.buffer.insert(ri.buffer.begin(), STATUS_CODE_BYTES_LENGTH, static_cast<unsigned char>(statusCode));

    if (statusCode == LOGOUT_RC || statusCode == GET_HIGH_SCORE_RC || statusCode == GET_ROOMS_RC)
        return ri;

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

    return ri;
}