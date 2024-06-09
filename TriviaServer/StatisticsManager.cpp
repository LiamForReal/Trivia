#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
	this->_db = new SqliteDataBase();
	if (!this->_db->open())
		throw std::runtime_error("Failed to open database!");
}

StatisticsManager::~StatisticsManager() 
{
	this->_db->close();
	delete _db;
}

vector<string> StatisticsManager::getHighScore()
{
	vector<string> fiveBestScores;
	list<User> users = _db->getUsers(); //calc win - (correctAnswers / totalAnswers) / (AvrageTime - numOfGames / 1000)
	std::cout << "0\n";
	map<string, double> userScores;
	double divCorrectAnsInTotal = 0.0, addAvrageToNumOfGames = 0.0, score = 0.0;
	string name = "";
	std::cout << "1\n";
	for (auto itU = users.begin(); itU != users.end(); ++itU)
	{
		if (_db->getNumOfTotalAnswers(itU->getName()) == 0 || _db->getPlayerAverageAnswerTime(itU->getName()) == 0 || _db->getNumOfTotalAnswers(itU->getName()) == 0)
		{
			userScores[itU->getName()] = 0;
			continue;
		}
		divCorrectAnsInTotal = _db->getNumOfCorrectAnswers(itU->getName()) / _db->getNumOfTotalAnswers(itU->getName());
		addAvrageToNumOfGames = _db->getPlayerAverageAnswerTime(itU->getName()) - (_db->getNumOfPlayerGames(itU->getName()) / 1000);
	    userScores[itU->getName()] = divCorrectAnsInTotal / addAvrageToNumOfGames;
	}
	std::cout << "2\n";
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
	std::cout << "3\n";
	return fiveBestScores;
}

vector<string> StatisticsManager::getUserStatistics(string username) const
{
	vector<string> userStatistics; //user statistics: number of games | number of correct answers | number of wrong answers | avrage time for answer
	int correctAnswers = 0.0;
	userStatistics.push_back(std::to_string(_db->getNumOfPlayerGames(username)));
	correctAnswers = _db->getNumOfCorrectAnswers(username);
	userStatistics.push_back(std::to_string(correctAnswers));
	userStatistics.push_back(std::to_string(_db->getNumOfTotalAnswers(username) - correctAnswers));
	userStatistics.push_back(std::to_string(_db->getPlayerAverageAnswerTime(username)));
	return userStatistics; 
}

void StatisticsManager::addNewQuestionStatistics(const QuestionStatistics q)
{
	this->_db->addNewQuestionStatistics(q);
}