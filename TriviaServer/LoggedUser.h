#pragma once
#include "includes.hpp"

class LoggedUser
{
public:
	LoggedUser();
	LoggedUser(string name);
	string getUserName() const;
	void setUserName(const string newUserName);
	bool operator==(const LoggedUser& other) const;
	bool operator<(const LoggedUser& other) const
	{
		return this->username < other.username;
	}

private:
	string username;
};
