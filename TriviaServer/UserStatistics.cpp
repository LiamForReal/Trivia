#include "UserStatistics.h"

UserStatistics::UserStatistics()
{
	this->_avrageTimeForAnswer = 0;
	this->_numberOfCorrectAnswers = 0;
	this->_numOfTotalAnswers = 0;
	this->_numberOfGames = 0;
}
UserStatistics::UserStatistics(int numberOfGames, int numberOfCorrectAnswers, int numOfTotalAnswers, int AvrageTimeForAnswer)
{
	this->_avrageTimeForAnswer = AvrageTimeForAnswer;
	this->_numberOfCorrectAnswers = numberOfCorrectAnswers;
	this->_numOfTotalAnswers = numOfTotalAnswers;
	this->_numberOfGames = numberOfGames;
}
UserStatistics::~UserStatistics() {}

int UserStatistics::getNumOfGames() const
{
	return this->_numberOfGames;
}

int UserStatistics::getNumOfCorrectAnswers() const
{
	return this->_numberOfCorrectAnswers;
}

int UserStatistics::getNumOfTotalAnswers() const
{
	return this->_numOfTotalAnswers;
}

float UserStatistics::getAvrageTimeForAnswer() const
{
	return this->_avrageTimeForAnswer;
}

void UserStatistics::setNumOfGames(const int newNumOfGames)
{
	this->_numberOfGames = newNumOfGames;
}

void UserStatistics::setNumOfCorrectAnswers(const int newNumOfCorrectAnswers)
{
	this->_numberOfCorrectAnswers = newNumOfCorrectAnswers;
}

void UserStatistics::setNumOfTotalAnswers(const int newNumOfTotalAnswers)
{
	this->_numOfTotalAnswers = newNumOfTotalAnswers;
}

void UserStatistics::setAvrageTimeForAnswer(const float newAvrageTimeForAnswer)
{
	this->_avrageTimeForAnswer = newAvrageTimeForAnswer;
}