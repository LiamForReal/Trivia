#pragma once
#include "Game.h"
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "QuestionStatistics.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(); //TODO to think of a better way to do this
	~GameManager();
	Game& createGame(Room room);
	void deleteGame(LoggedUser user);
	Game& getGame(LoggedUser user);
	list<Question> getTriviaQuestions();
	void setQuestionId(const int newQuestionId, LoggedUser user);
	void setAvrageTime(const float newAvrageTime, LoggedUser user);
private:
	std::map<LoggedUser, Game> games;
	IDatabase* db;
	int gameId;
};

