#pragma once
#include "IDatabase.h"
#include "includes.hpp"

class StatisticsManager
{
public:
	std::vector<string> getHighScore() const;
	std::vector<string> getUserStatistics(string username) const;
private:
	IDatabase* _db;
};

