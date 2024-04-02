#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp"

typedef enum ResponseCode
{
	ERROR_RC = 99,
	LOGIN_RC = 1,
	SIGNUP_RC = 2,
} ResponseCode;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;
};

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

class JsonResponsePacketSerializer
{
	public:
		static std::vector<unsigned char> serializeResponse(const ErrorResponse& errorResponse);
};

