#include "StatisticsManager.h"

vector<string> StatisticsManager::getHighScore() const
{
	vector<string> fiveBestScores;
	list<QuestionStatistics> questionsStatistics = _db->getQuestionsStatistics();
	for (auto it = questionsStatistics.begin(); it != questionsStatistics.end(); ++it)
	{
		//complit this 
		if()
	}
	return s;
}
vector<string> StatisticsManager::getUserStatistics(string username) const
{
	std::vector<string> s;
	return s;
}