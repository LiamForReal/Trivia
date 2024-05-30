#pragma once
#include "includes.hpp"
#include "Game.h"

class QuestionStatistics
{
public:
	QuestionStatistics(string username, float answerTime, bool isCorrect, string answe);
	QuestionStatistics(Game game, string username, bool isCorrect, string answer);
	~QuestionStatistics();

	string getUserName() const;
	string getAnswer() const;
	void setAnswer(const string ans);
	int getQuestionId() const;
	bool getIsCorrect() const;
	float getAnswerTime() const;
	int getGameId() const;

	void setUserName(const string newUserName);
	void setQuestionId(const int newQuestionId);
	void setIsCorrect(const bool newIsCorrect);
	void setAnswerTime(const float newAnswerTime);
	void setGameId(const int GameId);

private:
	string _username;
	string answer;
	int _gameId;
	int _questionId;
	bool _isCorrect;
	float _answerTime;
};
