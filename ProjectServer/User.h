#pragma once
#include "includes.hpp"

class User
{
public:

	User(string pass, string name, string email);
	~User();
	string getName() const;
	string getPass() const;
	string getMail() const;

	void setName(const string newName);
	void setPass(const string newPass);
	void setMail(const string newMail);

private:
	string _username;
	string _password;
	string _email;
};

