#pragma once
#include "SqliteDataBase.h"
#include "includes.hpp"
#include "QuestionStatistics.h"

/**
*	The purpose of StatisticsManager is to manage all of the users statistics in the Trivia.
*	It allows to get information about all of the users high scores and personal statistics.
*	The StatisticsManager is created only once during the runtime of the program,
*	and it's created inside of RequestHandlerFactory.
*
*	It holds a pointer to a SQLite Database.
*/

class StatisticsManager
{
public:
	StatisticsManager();
	~StatisticsManager();
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username) const;
	void addNewQuestionStatistics(const QuestionStatistics q);
private:
	IDatabase* _db;
};

