#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"

class LoginManager
{
public:

	void logout(const string name);
	void login(const string name, const string pass);
	void singup(const string name, const string pass, const string mail);

private:
	IDatabase* _dataBace;
	vector<LoggedUser> _loggedUsers;
};

