#pragma once
#include <vector>
#include <ctime>

class IRequestHandler; // Forward declaration

typedef struct RequestInfo // Changed from typedef to struct definition
{
    unsigned int id;
    std::time_t recievalTime;
    std::vector<unsigned char> buffer;

    RequestInfo(unsigned int id, std::time_t recievalTime)
    {
        this->id = id;
        this->recievalTime = recievalTime;
        this->buffer = std::vector<unsigned char>();
    }

    RequestInfo()
    {
        this->id = 0;
        this->recievalTime = NULL;
        this->buffer.clear();
    }
} RequestInfo;

typedef struct RequestResult // Changed from typedef to struct definition
{
    std::vector<unsigned char> buffer;
    IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
public:
    virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
    virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};