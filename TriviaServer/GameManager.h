#pragma once
#include "Game.h"
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "QuestionStatistics.h"
#include "Room.h"


/**
*	The purpose of GameManager is to manage all of the games in the Trivia.
*	It manages the creation or deletion of games,
*	and another useful data about all the games.
*	The GameManager is created only once during the runtime of the program,
*	and it's created inside of RequestHandlerFactory.
*
*	It uses a map of LoggedUser as key that represents the user of the current he is playing in,
*	and the value is the Game itself.
*	
*	It holds a pointer to a SQLite Database.
*/

class GameManager
{
public:
	GameManager();
	~GameManager();
	Game& createGame(Room room);
	void deleteGame(LoggedUser user);
	Game& getGame(LoggedUser user);
	/**
	* Returns all of the questions in the whole Trivia.
	*/
	list<Question> getTriviaQuestions();
	void setQuestionId(const int newQuestionId, LoggedUser user);
	/**
	* Sets the average time for the given user to answer a question.
	*/
	void setAvrageTime(const float newAvrageTime, LoggedUser user);
	void addNewQuestion(AddNewQuestionRequest anqr);
private:
	std::map<LoggedUser, Game> games;
	IDatabase* db;
	int gameId;
};

