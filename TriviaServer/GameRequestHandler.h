class RequestHandlerFactory;
#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "includes.hpp"
#include "defines.hpp"
#include "PlayerResults.hpp"
#include "QuestionStatistics.h"
#include "Room.h"
#include <random>
#include <chrono>

/**
* The GameRequestHandler inherits from IRequestHandler which is the base class for all Handlers.
* 
* The GameRequestHandler is created more than once, during a game.
* 
* The first data structure is a static map with a key which represents a room ID, which a value
* of pair of the vector of the Room's questions 
* and a map who has a key that represents the users in the Game and their questions progress 
* (amount of answered questions).
* 
* The question in each room is generated only once in the randQuestionsToRoom function for better efficiency.
* 
* The second data structure is a static map of the users in the game as keys,
* and an indicator for the average answer time on the questions.
* 
* The third data structure is a static map which has room IDs as keys and 
* the values are pairs which its first value is a Room that becomes empty users when they all finish
* all of the questions and progress to the waiting, and the second pair's value
* represents the amount of PlayerResults after the Room is empty of players.
* 
* When the game is successfully finished or,
* the user leaves in the middle of the game it advances to MenuRequestHandler.
* 
*/

class GameRequestHandler : virtual public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& rhf, LoggedUser user, unsigned int roomId);
	~GameRequestHandler();
	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	void randQuestionsToRoom();
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	RequestHandlerFactory& _rhf;
	LoggedUser _user;
	unsigned int _roomId;
	static map<unsigned int, std::pair<vector<Question>, std::map<LoggedUser,int>>> roomsQuestions;
	static map<LoggedUser, std::chrono::high_resolution_clock::time_point> avrageTime;
	static map<unsigned int, std::pair<Room, int>> getStatsRoom;
};

