#include "LoggedUser.h"

LoggedUser::LoggedUser()
{
	username = "";
}

LoggedUser::LoggedUser(string name)
{
	username = name;
}

string LoggedUser::getUserName() const
{
	return username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return this->username == other.username;
}
