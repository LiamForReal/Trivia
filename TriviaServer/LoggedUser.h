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


private:
	string username;
};

