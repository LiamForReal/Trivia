#pragma once
#include "includes.hpp"

class LoggedUser
{
public:
	LoggedUser(string name);
	string getUserName() const;

private:
	string username;
};

