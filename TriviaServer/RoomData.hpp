#pragma once
#include <string>
#include "json.hpp"
#include "Requests.hpp"

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;

	RoomData()
	{
		this->id = 0;
		this->name = "";
		this->maxPlayers = 0;
		this->numOfQuestionsInGame = 0;
		this->timePerQuestion = 0;
		this->isActive = false;
	}

	RoomData(unsigned int _id, std::string _name, unsigned int _maxPlayers, unsigned int _questionCount, unsigned int _avrageTime, unsigned int _active) 
	{
		this->id = _id;
		this->name = _name;
		this->maxPlayers = _maxPlayers;
		this->numOfQuestionsInGame = _questionCount;
		this->timePerQuestion = _avrageTime;
		this->isActive = _active;
	}

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RoomData, id, name, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive);	
} RoomData;