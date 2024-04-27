#pragma once
#include "includes.hpp"

class User
{
public:

	User(string pass, string name, string email);
	User(string pass, string name, string email, int id);
	~User();

	string getName() const;
	string getPass() const;
	string getMail() const;
	int getId() const;

	void setName(const string newName);
	void setPass(const string newPass);
	void setMail(const string newMail);
	void setId(const int newId);

private:
	string _username;
	string _password;
	string _email;
	int _id;
};

