#pragma once
#include "IDatabase.h"

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase() = default;
	virtual ~SqliteDataBase() = default;

	bool open() override;
	void close() override;

	bool isUserExist(const string name) override;
	bool isUserExist(const string name, const string pass) override;
	bool isPasswordMatch(const string password) override;
	void addNewUser(User& user) override;

	bool isBigLetter(int ch);
	bool isNumber(int ch);
	bool isSmallLetter(int ch);
	std::vector<User> getUsers();
	bool sendSQLMsg(const char* sql_command);
private:
	sqlite3* db;
};

