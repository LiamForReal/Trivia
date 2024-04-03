#pragma once
#include <vector>
#include <ctime>

typedef struct RequestInfo
{
	unsigned int id;
	// TODO: std::ctime recievalTime;
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
		virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
		virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};
