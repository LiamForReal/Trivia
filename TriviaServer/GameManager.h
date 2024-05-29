#pragma once
#include "Game.h"
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(LoggedUser user);
	~GameManager();
	Game createGame(Room room);
	void deleteGame();
	list<Question> getTriviaQuestions();

private:
	LoggedUser user;
	std::map<LoggedUser, Game> games;
	IDatabase* db;
};

