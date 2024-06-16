#pragma once
#include "LoggedUser.h"
#include "Room.h"
#include "includes.hpp"

/**
*	The purpose of RoomManager is to manage all of the rooms in the game.
*	It manages the creation or deletion of rooms, and also it helps to check the states of the rooms,
*	and another useful data about all the rooms.
*	The RoomManager is created only once during the runtime of the program, 
*	and it's created inside of RequestHandlerFactory.
* 
*	It uses a map of unsigned int as key that represents the room ID of each room,
*	and the value is the Room itself.
* 
* 	It holds a pointer to a SQLite Database.
*/

class RoomManager
{
	public:
		RoomManager();
		~RoomManager();
		void createRoom(const LoggedUser& user, const RoomData& roomData);
		void deleteRoom(const unsigned int& id);
		/**
		* Function that returns one of the possible values of the RoomDataActivityStates Enum
		*/
		unsigned int getRoomState(const unsigned int& id);
		std::vector<RoomData> getRooms();
		Room& getRoom(const unsigned int& id);
		bool isRoomExist(const unsigned int& id);
	private:
		std::map<unsigned int, Room> m_rooms;
};

