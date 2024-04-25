#include "Room.h"

void Room::addUser(const LoggedUser& user)
{
	this->m_users.insert(this->m_users.end(), user);
}

void Room::removeUser(const LoggedUser& user)
{
	auto it = std::find(this->m_users.begin(), this->m_users.end(), user);
	if (it != this->m_users.end())
	{
		this->m_users.erase(it);
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> vec;

	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		vec.insert(vec.end(), it->getUserName());
	}

	return vec;
}
