#pragma once
#include "SqliteDataBase.h"
#include "includes.hpp"

class StatisticsManager
{
public:
	StatisticsManager();
	~StatisticsManager();
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username) const;
private:
	IDatabase* _db;
};

