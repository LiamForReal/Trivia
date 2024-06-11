#pragma once
#include "SqliteDataBase.h"
#include "includes.hpp"
#include "QuestionStatistics.h"

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

