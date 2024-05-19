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
	delete _dataBace;
}

void LoginManager::logout(const string name)
{
	std::cout << "logged users vector: \n";
	for (int i = 0; i < _loggedUsers.size(); ++i)
	{
		std::cout << _loggedUsers[i].getUserName() << std::endl;
		if (_loggedUsers[i].getUserName() == name)
		{
			_loggedUsers.erase(_loggedUsers.begin() + i);
			return;
		}
	}
	throw std::runtime_error("faild to logout");
}

unsigned int LoginManager::login(const string name, const string pass)
{
	auto it = std::find(_loggedUsers.begin(), _loggedUsers.end(), LoggedUser(name));

	if (_dataBace->isUserExist(name, pass) && it == _loggedUsers.end())
	{
		this->_loggedUsers.push_back(LoggedUser(name));
		std::cout << "logged successfully!\n";
		return LOGIN_STATUS;
	}
	std::cout << "user not in the system or already logged!\n";
	return LOGIN_ERROR;
}

unsigned int LoginManager::singup(const string name, const string pass, const string mail)
{
	
	if (!_dataBace->isUserExist(name) && _dataBace->isPasswordMatch(pass))
	{
		User user = User(pass, name, mail);
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

vector<LoggedUser> LoginManager::getLoggedUsers() const
{
	return this->_loggedUsers;
}