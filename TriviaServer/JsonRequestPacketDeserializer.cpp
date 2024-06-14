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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const std::vector<unsigned char>& buffer)
{
	GetPlayersInRoomRequest gpirr;
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
		gpirr.roomId = jsonData["roomId"];
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed");
	}

	return gpirr;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer)
{
	JoinRoomRequest jrr;
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
		jrr.roomId = jsonData["roomId"];
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed");
	}

	return jrr;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer)
{
	CreateRoomRequest crr;
	std::string jsonDataStr = "", tmp = "";
	unsigned int len = 0, i = 0, t = 0;

	memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	// std::cout << len << std::endl;

	for (i = 0; i < len; i++)
	{
		jsonDataStr += buffer[BYTES_TO_COPY + INC + i];
	}

	json jsonData = json::parse(jsonDataStr);

	try
	{
		crr.roomName = jsonData["roomName"];
		tmp = jsonData["maxUsers"];
		crr.maxUsers = static_cast<unsigned int>(std::stoi(tmp));
		tmp = jsonData["questionsCount"];
		crr.questionsCount = static_cast<unsigned int>(std::stoi(tmp));
		tmp = jsonData["answerTimeout"];
		crr.answerTimeout = static_cast<unsigned int>(std::stoi(tmp));

		tmp = jsonData["isMatchMake"];
		crr.isMatchMake = static_cast<bool>(std::stoi(tmp));
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed" + std::to_string(t));
	}

	return crr;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const std::vector<unsigned char>& buffer)
{
	SubmitAnswerRequest sar;
	std::string jsonDataStr = "";
	unsigned int len = 0, i = 0;

	std::memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	std::cout << len << std::endl;

	for (i = 0; i < len; i++)
	{
		jsonDataStr += buffer[BYTES_TO_COPY + INC + i];
	}
	std::cout << jsonDataStr;
	json jsonData = json::parse(jsonDataStr);

	try
	{
		sar.answer = jsonData["answer"];
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed");
	}
	return sar;
}

AddNewQuestionRequest JsonRequestPacketDeserializer::deserializeAddNewQuestionRequest(const std::vector<unsigned char>& buffer)
{
	AddNewQuestionRequest anqr = AddNewQuestionRequest();
	std::string jsonDataStr = "";
	unsigned int len = 0, i = 0;

	std::memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	std::cout << len << std::endl;

	for (i = 0; i < len; i++)
	{
		jsonDataStr += buffer[BYTES_TO_COPY + INC + i];
	}
	std::cout << jsonDataStr;

	json jsonData = json::parse(jsonDataStr);

	try 
	{
		anqr.question = jsonData["question"];
		anqr.correctAnswer = jsonData["correctAnswer"];
		anqr.wrongAnswer1 = jsonData["wrongAnswer1"];
		anqr.wrongAnswer2 = jsonData["wrongAnswer2"];
		anqr.wrongAnswer3 = jsonData["wrongAnswer3"];
	}
	catch (...)
	{
		throw std::runtime_error("Invalid json structure passed");
	}

	return anqr;
}
