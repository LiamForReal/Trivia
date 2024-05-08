#pragma once
#include <vector>
#include <ctime>

class IRequestHandler; // Forward declaration

struct RequestInfo // Changed from typedef to struct definition
{
    unsigned int id;
    std::time_t recievalTime;
    std::vector<unsigned char> buffer;
};

struct RequestResult // Changed from typedef to struct definition
{
    std::vector<unsigned char> buffer;
    IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
    virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
    virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};