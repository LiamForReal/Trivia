#pragma once
#include <vector>
#include <ctime>

typedef struct RequestInfo
{
	unsigned int id;
	std::time_t recievalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<unsigned char> buffer;
	class IReqeustHandler* newHandler;
} RequestResult;

class IRequestHandler
{
	public:
		static bool isRequestRelevant(const RequestInfo& requestInfo);
		static RequestResult handleRequest(const RequestInfo& requestInfo);
};
