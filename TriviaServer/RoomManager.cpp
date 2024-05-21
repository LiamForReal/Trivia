#include "RoomManager.h"

RoomManager::RoomManager()
{
	this->m_rooms = map<unsigned int, Room>();
}
RoomManager::~RoomManager() {}

void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	Room room = Room(roomData);
	room.addUser(user);
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		if (room == it->second)
			throw std::runtime_error("room with this name already exist");
	}
	this->m_rooms.insert({roomData.id, room});
}

void RoomManager::deleteRoom(const unsigned int& id)
{
	if (isRoomExist(id))
		this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(const unsigned int& id)
{
	if (isRoomExist(id))
		return this->m_rooms[id].getMetadata().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> vec = std::vector<RoomData>();

	for (auto it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		vec.insert(vec.end(), it->second.getMetadata());
	}

	return vec;
}

Room& RoomManager::getRoom(const unsigned int& id)
{
	if(isRoomExist(id))
		return std::ref(this->m_rooms[id]);
}

bool RoomManager::isRoomExist(const unsigned int& id)
{
	if (m_rooms.find(id) != m_rooms.end())
		return true;
	return false;
}