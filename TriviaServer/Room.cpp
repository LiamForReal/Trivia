#include "Room.h"

Room::Room() {}

Room::Room(const RoomData& metadata)
{
	m_users = std::vector<LoggedUser>();
	this->m_metadata = metadata;
}

Room::~Room()
{
	this->m_users.clear();
}

void Room::addUser(const LoggedUser& user)
{
	if (!m_metadata.isActive && m_metadata.maxPlayers >= m_users.size() + 1)
		this->m_users.insert(this->m_users.end(), user);
	else throw std::runtime_error("can't insert to room");
}

void Room::removeUser(const LoggedUser& user)
{
	auto it = std::find(this->m_users.begin(), this->m_users.end(), user);
	if (it != this->m_users.end())
		this->m_users.erase(it);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> vec = std::vector<std::string>();
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		vec.push_back(it->getUserName());
	}
	return vec;
}

void Room::setRoomStatus(const unsigned int newStatus)
{
	this->m_metadata.isActive = newStatus;
}

void Room::setMetadata(const RoomData& metadata)
{
	this->m_metadata.id = metadata.id;
	this->m_metadata.isActive = metadata.isActive;
	this->m_metadata.name = metadata.name;
	this->m_metadata.maxPlayers = metadata.maxPlayers;
	this->m_metadata.numOfQuestionsInGame = metadata.numOfQuestionsInGame;
	this->m_metadata.timePerQuestion = metadata.timePerQuestion;
}

RoomData Room::getMetadata() const
{
	RoomData deepcopied = RoomData();
	deepcopied.id = this->m_metadata.id;
	deepcopied.isActive = this->m_metadata.isActive;
	deepcopied.maxPlayers = this->m_metadata.maxPlayers;
	deepcopied.name = this->m_metadata.name;
	deepcopied.numOfQuestionsInGame = this->m_metadata.numOfQuestionsInGame;
	deepcopied.timePerQuestion = this->m_metadata.timePerQuestion;
	return deepcopied;
}

bool Room::operator==(const Room& other) const
{
	return this->m_metadata.name == other.m_metadata.name;
}