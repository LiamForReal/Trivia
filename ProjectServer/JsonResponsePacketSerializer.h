#pragma once
#include <string>
#include <vector>
#include "json.hpp"

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
		static std::vector<unsigned char> serializeResponse();
};

