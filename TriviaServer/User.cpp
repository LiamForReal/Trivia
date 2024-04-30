#include "User.h"

User::User(string pass, string name, string email)
{
	_password = pass;
	_username = name;
	_email = email;
	_id = -1;
}

User::User(string pass, string name, string email, int id)
{
	_password = pass;
	_username = name;
	_email = email;
	_id = id;
}

User::~User() {} //nothing to diconstruct

string User::getName() const
{
	return _username;
}
string User::getPass() const
{
	return _password;
}
string User::getMail() const
{
	return _email;
}

int User::getId() const
{
	return _id;
}

void User::setId(const int newId)
{
	_id = newId;
}

void User::setName(const string newName)
{
	_username = newName;
}

void User::setPass(const string newPass)
{
	_password = newPass;
}

void User::setMail(const string newMail)
{
	_email = newMail;
}