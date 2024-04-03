#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp"
#include "Responses.hpp"

class JsonResponsePacketSerializer
{
	public:
		static std::vector<unsigned char> serializeResponse(const ErrorResponse& errorResponse);
		static std::vector<unsigned char> serializeResponse(const LoginResponse& loginResponse);
		static std::vector<unsigned char> serializeResponse(const SignupResponse& signupResponse);
};

