#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "Responses.hpp"

/**
*	The purpose of LoginManager is to manage all of the users in the Trivia.
*	It manages the login, sign up, and logout "processes" of users to the Trivia,
*	and another useful data about all the users.
*	The LoginManager is created only once during the runtime of the program,
*	and it's created inside of RequestHandlerFactory.
*
*	It uses a static vector of all the logged users to the Trivia,
*   it's content of logged users according to logins and logouts.
*
*	It holds a pointer to a SQLite Database.
*/


class LoginManager
{
public:

	LoginManager();
	~LoginManager();
	vector<LoggedUser> getLoggedUsers() const;
	void logout(const string name);
	unsigned int login(const string name, const string pass);
	unsigned int singup(const string name, const string pass, const string mail);

private:
	IDatabase* _dataBace;
	static vector<LoggedUser> _loggedUsers;
};

