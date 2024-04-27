#pragma once
#include "IDatabase.h"

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase() = default;
	 ~SqliteDataBase() = default;

	bool open() override;
	void close() override;

	bool isUserExist(const string name) override;
	bool isUserExist(const string name, const string pass) override;
	bool isPasswordMatch(const string password) override;
	void addNewUser(User& user) override;
	void addNewQuestion(Question question) override;
	float getPlayerAverageAnswerTime(string username) override;
	int getNumOfCorrectAnswers(string username) override;
	int getNumOfTotalAnswers(string username) override;
	int getNumOfPlayerGames(string username) override;

	list<QuestionStatistics> getQuestionsStatistics() override;
	list<User> getUsers() override;
	list<Question> getQuestions() override;
	
	bool isBigLetter(int ch);
	bool isNumber(int ch);
	bool isSmallLetter(int ch);
	bool sendSQLMsg(const char* sql_command);
private:
	sqlite3* db;
};

