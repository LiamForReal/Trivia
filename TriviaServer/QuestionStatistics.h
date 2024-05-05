#pragma once
#include "includes.hpp"
class QuestionStatistics
{
public:
	QuestionStatistics(string username, string answer, time_t answerTime, bool isCorrect);
	QuestionStatistics(string username, string answer, time_t answerTime, bool isCorrect, int questionId);
	~QuestionStatistics();

	string getUserName() const;
	string getPlayerAnswer() const;
	int getQuestionId() const;
	bool getIsCorrect() const;
	time_t getAnswerTime() const;
	int getGameId() const;

	void setUserName(const string newUserName);
	void setPlayerAnswer(const string newPlayerAnswer);
	void setQuestionId(const int newQuestionId);
	void setIsCorrect(const bool newIsCorrect);
	void setAnswerTime(const time_t newAnswerTime);
	void setGameId(const int GameId);

private:
	string _username;
	int _gameId;
	int _questionId;
	string _playerAnswer;
	bool _isCorrect;
	time_t _answerTime;
};
