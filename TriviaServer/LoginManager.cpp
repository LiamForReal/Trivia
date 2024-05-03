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

unsigned int LoginManager::logout(const string name)
{
	for (int i = 0; i < _loggedUsers.size(); ++i)
	{
		if (_loggedUsers[i].getUserName() == name)
		{
			_loggedUsers.erase(_loggedUsers.begin() + i);
			return LOGOUT_STATUS;
		}
	}
	return LOGOUT_ERROR;
}

unsigned int LoginManager::login(const string name, const string pass)
{
	int i = _loggedUsers.size() - 1;
	if (!_loggedUsers.empty())
	{
		for (i = 0; i < _loggedUsers.size(); ++i)
		{
			if (_loggedUsers[i].getUserName() == name)
				break;
		}
	}
	
	if (_dataBace->isUserExist(name, pass) && i == _loggedUsers.size() - 1)
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
	
	if (!_dataBace->isUserExist(name) && _dataBace->isPasswordMatch(pass))
	{
		User user = User(pass, name, mail);
		this->_loggedUsers.push_back(LoggedUser(name));
		_dataBace->addNewUser(user);
		std::cout << "signup successfully!\n";
		return SIGNUP_STATUS;
	}
	else if (!_dataBace->isPasswordMatch(pass))
	{
		std::cout << "your password is to week\n";
		return PASSWORD_WEAK;
	}
	std::cout << "user name is already in the system\n";
	return SIGNUP_ERROR;
}