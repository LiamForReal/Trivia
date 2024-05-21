#pragma once
#include <string>
#include "json.hpp"
#include "Requests.hpp"

typedef enum RoomDataActivityStates
{
	ACTIVE_ROOM = 1,
	INACTIVE_ROOM = 0,
} RoomDataActivityStates;

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

	RoomData& operator=(const RoomData& other)
	{
		this->id = other.id;
		this->name = other.name;
		this->maxPlayers = other.maxPlayers;
		this->numOfQuestionsInGame = other.numOfQuestionsInGame;
		this->timePerQuestion = other.timePerQuestion;
		this->isActive = other.isActive;
		
		return *this;
	}

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RoomData, id, name, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive);	
} RoomData;