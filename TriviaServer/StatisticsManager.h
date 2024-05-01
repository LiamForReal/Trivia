#pragma once
#include "IDatabase.h"
#include "includes.hpp"

class StatisticsManager
{
public:
	vector<string> getHighScore() const;
	string getUserStatistics(string username) const;
private:
	IDatabase* _db;
};

