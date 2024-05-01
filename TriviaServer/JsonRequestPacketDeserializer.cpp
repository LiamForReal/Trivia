#include "JsonRequestPacketDeserializer.h"
#include <iostream> // for debug

#include "defines.hpp"

using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
	LoginRequest lr;
	std::string jsonDataStr = "";

	unsigned int len = 0, i = 0;

	memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);

	for (i = 0; i < len; i++)
	{
		jsonDataStr += buffer[BYTES_TO_COPY + INC + i];
	}

	json jsonData = json::parse(jsonDataStr);

	try
	{
		lr.username = jsonData["username"];
		lr.password = jsonData["password"];
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed");
	}

	return lr;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& buffer)
{
	SignupRequest sr;
	std::string jsonDataStr = "";

	unsigned int len = 0, i = 0;

	memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	// std::cout << len << std::endl;

	for (i = 0; i < len; i++)
	{
		jsonDataStr += buffer[BYTES_TO_COPY + INC + i];
	}

	json jsonData = json::parse(jsonDataStr);

	try
	{
		sr.username = jsonData["username"];
		sr.password = jsonData["password"];
		sr.email = jsonData["email"];
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed");
	}

	return sr;
}