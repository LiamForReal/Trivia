#include "StatisticsManager.h"

vector<string> StatisticsManager::getHighScore() const
{
	vector<string> fiveBestScores;
	list<User> users = _db->getUsers(); //calc win - (correctAnswers / totalAnswers) / (AvrageTime - numOfGames / 100)
	map<string, double> userScores;
	double divCorrectAnsInTotal = 0.0, addAvrageToNumOfGames = 0.0, score = 0.0;
	string name = "";
	for (auto itU = users.begin(); itU != users.end(); ++itU)
	{
		divCorrectAnsInTotal = _db->getNumOfCorrectAnswers(itU->getName()) / _db->getNumOfTotalAnswers(itU->getName());
		addAvrageToNumOfGames = _db->getPlayerAverageAnswerTime(itU->getName()) - (_db->getNumOfPlayerGames(itU->getName()) / 100);
		userScores[itU->getName()] = divCorrectAnsInTotal / addAvrageToNumOfGames;
	}
	
	for (int i = 0; i < 5; i++)
	{
		if (!userScores.empty())
		{
			for (auto it = userScores.begin(); it != userScores.end(); ++it)
			{
				if (score < it->second)
				{
					score = it->second;
					name = it->first;
				}
			}
			fiveBestScores.push_back(name);
			userScores.erase(name);
			name = "";
			score = 0;
		}
	}
	return fiveBestScores;
}

string StatisticsManager::getUserStatistics(string username) const
{
	string userStatistics; //user statistics: number of games | number of correct answers | number of wrong answers | avrage time for answer
	double correctAnswers = 0.0;
	userStatistics += std::to_string(_db->getNumOfPlayerGames(username)) + "|";
	correctAnswers = _db->getNumOfCorrectAnswers(username);
	userStatistics += std::to_string(correctAnswers) + "|";
	userStatistics += std::to_string(_db->getNumOfTotalAnswers(username) - correctAnswers) + "|";
	userStatistics += std::to_string(_db->getPlayerAverageAnswerTime(username));
	return userStatistics; 
}