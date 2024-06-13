#include "Communicator.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include <iostream>
#include <vector>
#include "defines.hpp"
#include "MenuRequestHandler.h"
#include <mutex>

//std::mutex mtx; FIND WAY TO COMBINE IT

Communicator::Communicator()
{
    this->rhf = new RequestHandlerFactory();
}

Communicator::~Communicator()
{
    for (auto it = _handlers.begin(); it != _handlers.end(); ++it)
    {
        delete it->second;
        _handlers.erase(it);
    }
    delete rhf;
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
    unsigned int statusCode = 0, size = 0;
    RequestInfo ri = RequestInfo();
    RequestResult rr = RequestResult();
    LoggedUser loggedUser = LoggedUser();
    _handlers[clientSocket] = rhf->creatLoginRequestHandler();
    rr.newHandler = _handlers[clientSocket];
    rr.buffer = std::vector<unsigned char>();

    try
    {
        size = rhf->getLoginMeneger().getLoggedUsers().size();
        while (true)
        {
            if (loggedUser.getUserName() == "")
            {
                do
                {
                    statusCode = Helper::socketHasData(clientSocket);
                    if (statusCode != 0 && statusCode != -1)
                    {
                        std::cout << "LOGIN REQUEST HANDLER\n\n";
                        ri = buildRI(clientSocket, statusCode);
                        std::cout << "DEBUG REQUEST CODE: " << ri.id << std::endl;
                        rr = rr.newHandler->handleRequest(ri);
                        _handlers[clientSocket] = rr.newHandler;
                        Helper::sendVector(clientSocket, std::ref(rr.buffer));
                        std::cout << "DEBUG RESPONSE CODE: " << (unsigned int)rr.buffer[0] << std::endl;
                    }
                } while (rhf->getLoginMeneger().getLoggedUsers().size() == size);
                loggedUser = LoggedUser(JsonRequestPacketDeserializer::deserializeLoginRequest(ri.buffer).username);
                std::cout << "DEBUG: user login: " << loggedUser.getUserName() << std::endl;
            }

            do
            {
                statusCode = Helper::socketHasData(clientSocket);
                if (statusCode != 0 && statusCode != -1)
                {
                    std::cout << "MENU REQUEST HANDLER " << loggedUser.getUserName() << "\n\n";
                    ri = buildRI(clientSocket, statusCode);

                    try
                    {
                        std::cout << _handlers[clientSocket]->isRequestRelevant(ri) << std::endl;
                    }
                    catch (std::runtime_error& e)
                    {
                        std::cout << e.what() << std::endl;
                    }

                    if (_handlers[clientSocket]->isRequestRelevant(ri) || ri.id == GET_ROOMS_RC)
                    {
                        try
                        {
                            rr = _handlers[clientSocket]->handleRequest(ri);
                            std::cout << "DEBUG: response code " << (unsigned int)(rr.buffer[0]) << std::endl;
                            Helper::sendVector(clientSocket, rr.buffer);
                        }
                        catch (std::runtime_error& e)
                        {
                            if (ri.id == GET_ROOMS_RC)
                            {
                                Helper::sendVector(clientSocket, this->rhf->createMenuRequestHandler(loggedUser)->getRooms(ri).buffer);
                            }
                            else throw e;
                        }

                        if ((unsigned int)rr.buffer[0] == LOGOUT_STATUS)
                        {
                            std::cout << "DEBUG: user logout: " << loggedUser.getUserName();
                            _handlers[clientSocket] = rhf->creatLoginRequestHandler();
                            loggedUser.setUserName("");
                        }
                    }

                    _handlers[clientSocket] = rr.newHandler;
                }
            } while (loggedUser.getUserName() != "");
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

    if (statusCode == LOGOUT_RC || statusCode == GET_HIGH_SCORE_RC || statusCode == GET_ROOMS_RC ||
        statusCode == GET_PERSONAL_STATS_RC || statusCode == LEAVE_ROOM_RC || statusCode == START_GAME_RC ||
        statusCode == CLOSE_ROOM_RC || statusCode == GET_ROOM_STATE_RC || statusCode == GET_QUESTION_RC || 
        statusCode == LEAVE_GAME_RC || statusCode == GET_GAME_RESULTS_RC)
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

std::map<SOCKET, IRequestHandler*> Communicator::getHandlers() const
{
    return this->_handlers;
}