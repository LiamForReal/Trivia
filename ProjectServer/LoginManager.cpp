#include "LoginManager.h"

std::vector<LoggedUser> LoginManager::_loggedUsers;

LoginManager::LoginManager()
{
	_dataBace = new SqliteDataBase();
	if (!this->_dataBace->open())
		throw std::runtime_error("Failed to open database!");
}

LoginManager::~LoginManager()
{
	this->_dataBace->close();
}

void LoginManager::logout(const string name)
{
	for (int i = 0; i < _loggedUsers.size(); ++i)
	{
		if (_loggedUsers[i].getUserName() == name)
		{
			_loggedUsers.erase(_loggedUsers.begin() + i);
			return;
		}
			
	}
}

unsigned int LoginManager::login(const string name, const string pass)
{
	auto it = _loggedUsers.begin();
	for (it = _loggedUsers.begin(); it != _loggedUsers.end(); ++it)
	{
		if (it->getUserName() == name)
			break;
		//std::cout << "it: " << it->getUserName() << " == name: " << name;
	}
	if (_dataBace->isUserExist(name, pass) && it == _loggedUsers.end())
	{
		this->_loggedUsers.push_back(LoggedUser(name));
		std::cout << "logged successfully!\n";
		return LOGIN_STATUS;
	}
	std::cout << "user not in the system or already loggeed!\n";
	return LOGIN_ERROR;
}

unsigned int LoginManager::singup(const string name, const string pass, const string mail)
{
	
	if (!_dataBace->isUserExist(name))
	{
		User user = User(pass, name, mail);
		this->_loggedUsers.push_back(LoggedUser(name));
		_dataBace->addNewUser(user);
		std::cout << "signup successfully!\n";
		return SIGNUP_STATUS;
	}
	std::cout << "user name is already in the system\n";
	return SIGNUP_ERROR;
}