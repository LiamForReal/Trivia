#include "LoginManager.h"

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

void LoginManager::login(const string name, const string pass)
{
	auto it = std::find(_loggedUsers.begin(), _loggedUsers.end(), LoggedUser(name));
	if (_dataBace->isUserExist(name, pass) && it != _loggedUsers.end())
		this->_loggedUsers.push_back(LoggedUser(name));
	else std::cout << "user not in the system or alrready loggeed!\n";
}

void LoginManager::singup(const string name, const string pass, const string mail)
{
	
	if (!_dataBace->isUserExist(name))
	{
		User user = User(pass, name, mail);
		_dataBace->addNewUser(user);
	}
	else std::cout << "user name is already in the system\n";
}