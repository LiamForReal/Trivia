#include "JsonRequestPacketDeserializer.h"
#include <iostream> // for debug

using json = nlohmann::json;

#define INC 1
#define BYTES_TO_COPY 4

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
	LoginRequest lr;
	std::string jsonDataStr = "";

	unsigned int len = 0, i = 1;

	memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	// std::cout << len << std::endl;

	for (i = 1; i <= len; i++)
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

	unsigned int len = 0, i = 1;

	memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	// std::cout << len << std::endl;

	for (i = 1; i <= len; i++)
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
