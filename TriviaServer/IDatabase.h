#pragma once
#include "includes.hpp"
#include "User.h"
#include "Question.h"
#include "QuestionStatistics.h"

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual bool isUserExist(const string name) = 0;
	virtual bool isUserExist(const string name, const string pass) = 0;
	virtual bool isPasswordMatch(const string password) = 0;
	virtual void addNewUser(User& user) = 0;
	virtual void addNewQuestion(Question question) = 0;
	virtual void addNewQuestionStatistics(QuestionStatistics stats) = 0;
	virtual list<User> getUsers() = 0;
	virtual list<Question> getQuestions() = 0;
	virtual list<QuestionStatistics> getQuestionsStatistics() = 0;
	virtual float getPlayerAverageAnswerTime(string username) = 0;
	virtual int getNumOfCorrectAnswers(string username) = 0;
	virtual int getNumOfTotalAnswers(string username) = 0;
	virtual int getNumOfPlayerGames(string username) = 0;
};