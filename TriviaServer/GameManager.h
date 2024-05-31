#pragma once
#include "Game.h"
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(LoggedUser user); //TODO to think of a better way to do this
	~GameManager();
	Game createGame(Room room);
	void deleteGame();
	Game getGame(LoggedUser user);
	list<Question> getTriviaQuestions();

private:
	LoggedUser user;
	std::map<LoggedUser, Game> games;
	IDatabase* db;
	static int gameId;
};

