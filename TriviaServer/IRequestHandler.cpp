#include "IRequestHandler.h"

bool IRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    return false;
}

RequestResult IRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    return RequestResult();
}
