#include "StatisticsManager.h"

vector<string> StatisticsManager::getHighScore() const
{
	vector<string> fiveBestScores;
	list<QuestionStatistics> questionsStatistics = _db->getQuestionsStatistics();
	list<User> users = _db->getUsers();
	for (auto it = questionsStatistics.begin(); it != questionsStatistics.end(); ++it)
	{

	}
}
vector<string> StatisticsManager::getUserStatistics(string username) const
{
	std::vector<string> s;
	return s;
}