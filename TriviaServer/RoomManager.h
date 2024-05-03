#pragma once
#include "LoggedUser.h"
#include "Room.h"
#include "includes.hpp"
#include <map>

class RoomManager
{
	public:
		void createRoom(const LoggedUser& user, const RoomData& roomData);
		void deleteRoom(const unsigned int& id);
		unsigned int getRoomState(const unsigned int& id);
		std::vector<RoomData> getRooms();
		Room& getRoom(const unsigned int& id);
		bool isLegalRoom(const unsigned int& id);
	private:
		std::map<unsigned int, Room> m_rooms;
};

