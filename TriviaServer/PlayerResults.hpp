#pragma once
#include <string>
#include "json.hpp"

typedef struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;

	PlayerResults()
	{
		this->username = "";
		this->correctAnswerCount = 0;
		this->wrongAnswerCount = 0;
		this->averageAnswerTime = 0.0f;
	}

	PlayerResults(const std::string& username, const unsigned int& correctAnswerCount, const unsigned int& wrongAnswerCount, const double& averageAnswerTime)
	{
		this->username = username;
		this->correctAnswerCount = correctAnswerCount;
		this->wrongAnswerCount = wrongAnswerCount;
		this->averageAnswerTime = averageAnswerTime;
	}

	PlayerResults& operator=(const PlayerResults& other)
	{
		if (nullptr == &other || this == &other)
		{
			return *this;
		}

		this->username = other.username;
		this->correctAnswerCount = other.correctAnswerCount;
		this->wrongAnswerCount = other.wrongAnswerCount;
		this->averageAnswerTime = other.averageAnswerTime;

		return *this;
	}

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerResults, username, correctAnswerCount, wrongAnswerCount, averageAnswerTime);
} PlayerResults;