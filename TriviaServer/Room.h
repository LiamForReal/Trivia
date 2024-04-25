#pragma once
#include "includes.hpp"
#include "LoggedUser.h"

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
	public:
		void addUser(const LoggedUser& user);
		void removeUser(const LoggedUser& user);
		std::vector<std::string> getAllUsers();

	private:
		RoomData m_metadata;
		std::vector<LoggedUser> m_users;
};