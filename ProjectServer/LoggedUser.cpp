#include "LoggedUser.h"

LoggedUser::LoggedUser(string name)
{
	username = name;
}

string LoggedUser::getUserName() const
{
	return username;
}
