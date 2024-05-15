#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	Room room = Room(roomData);
	this->m_rooms.insert({roomData.id, room});
	/*use user*/
}

void RoomManager::deleteRoom(const unsigned int& id)
{
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(const unsigned int& id)
{
	auto it = this->m_rooms.find(id);
	if (it != this->m_rooms.end())
	{
		return this->m_rooms[id].getMetadata().isActive;
	}
	return -1; // error that might occur
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> vec;

	for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		vec.push_back(it->second.getMetadata());
	}

	return vec;
}

Room& RoomManager::getRoom(const unsigned int& id)
{
	return std::ref(this->m_rooms[id]);
}

bool RoomManager::isLegalRoom(const unsigned int& id)
{
	return bool(getRooms().size());
}