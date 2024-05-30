#include "QuestionStatistics.h"

QuestionStatistics::QuestionStatistics(string username, float answerTime, bool isCorrect)
{
	this->_username = username;
	this->_isCorrect = isCorrect;
	this->_answerTime = answerTime;
	this->_questionId = -1;
	this->_gameId = -1;
}

QuestionStatistics::QuestionStatistics(string username, float answerTime, bool isCorrect, int questionId)
{
	this->_username = username;
	this->_isCorrect = isCorrect;
	this->_answerTime = answerTime;
	this->_questionId = questionId;
	this->_gameId = -1;
}

QuestionStatistics::QuestionStatistics(Game game, string username, bool isCorrect)
{
	this->_username = username;
	this->_isCorrect = isCorrect;
	this->_answerTime = game.getAvrageTime();
	this->_questionId = game.getQuestionId();
	this->_gameId = game.getGameId();
}

QuestionStatistics::~QuestionStatistics() {}

string QuestionStatistics::getUserName() const
{
	return this->_username;
}
int QuestionStatistics::getQuestionId() const
{
	return this->_questionId;
}
bool QuestionStatistics::getIsCorrect() const
{
	return this->_isCorrect;
}
float QuestionStatistics::getAnswerTime() const
{
	return this->_answerTime;
}

void QuestionStatistics::setUserName(const string newUserName)
{
	this->_username = newUserName;
}
void QuestionStatistics::setQuestionId(const int newQuestionId)
{
	this->_questionId = newQuestionId;
}
void QuestionStatistics::setIsCorrect(const bool newIsCorrect)
{
	this->_isCorrect = newIsCorrect;
}
void QuestionStatistics::setAnswerTime(const float newAnswerTime)
{
	this->_answerTime = newAnswerTime;
}
int QuestionStatistics::getGameId() const
{
	return this->_gameId;
}
void QuestionStatistics::setGameId(const int GameId)
{
	this->_gameId = GameId;
}