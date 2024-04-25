#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "Responses.hpp"

class LoginManager
{
public:

	LoginManager();
	~LoginManager();
	void logout(const string name);
	unsigned int login(const string name, const string pass);
	unsigned int singup(const string name, const string pass, const string mail);

private:
	IDatabase* _dataBace;
	static vector<LoggedUser> _loggedUsers;
};

