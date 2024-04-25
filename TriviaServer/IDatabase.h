#pragma once
#include "includes.hpp"
#include "User.h"

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual bool isUserExist(const string name) = 0;
	virtual bool isUserExist(const string name, const string pass) = 0;
	virtual bool isPasswordMatch(const string password) = 0;
	virtual void addNewUser(User& user) = 0;
	virtual std::vector<User> getUsers() = 0;
};