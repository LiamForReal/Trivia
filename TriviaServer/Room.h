#pragma once
#include "includes.hpp"
#include "LoggedUser.h"

class Room
{
	public:
		Room();
		Room(const RoomData& metadata);
		~Room();
		void addUser(const LoggedUser& user);
		void removeUser(const LoggedUser& user);
		std::vector<std::string> getAllUsers();
		RoomData getMetadata() const;
		void setRoomStatus(const unsigned int newStatus);
		void setMetadata(const RoomData& metadata);
		bool operator==(const Room& other) const;

	private:
		RoomData m_metadata;
		std::vector<LoggedUser> m_users;
};