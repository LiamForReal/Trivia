#include "LoggedUser.h"

LoggedUser::LoggedUser()
{
	username = "";
}

LoggedUser::LoggedUser(string name)
{
	username = name;
}

void LoggedUser::setUserName(const string newUserName)
{
	this->username = newUserName;
}

string LoggedUser::getUserName() const
{
	return username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return this->username == other.username;
}
