#pragma once
#include "includes.hpp"

class LoggedUser
{
public:
	LoggedUser(string name);
	string getUserName() const;

	bool operator==(const LoggedUser& other);

private:
	string username;
};

