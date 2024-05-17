#pragma once
#include "IDatabase.h"
#include "includes.hpp"

class StatisticsManager
{
public:
	vector<string> getHighScore() const;
	vector<string> getUserStatistics(string username) const;
private:
	IDatabase* _db;
};

