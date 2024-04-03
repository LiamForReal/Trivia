#pragma once
#include "json.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeserializer
{
	public:
		static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);
		static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);
};

