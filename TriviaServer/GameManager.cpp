#include "GameManager.h"
#include <stdexcept>

int GameManager::gameId = 0;

GameManager::GameManager(LoggedUser user) : user(user)
{
    db = new SqliteDataBase();
    if (!this->db->open())
        throw std::runtime_error("Failed to open database!");
}

GameManager::~GameManager()
{
    this->db->close();
    delete this->db;
}

Game GameManager::getGame(LoggedUser user)
{
    return this->games[user];
}

Game GameManager::createGame(Room room)
{
    for (const auto& it : room.getAllUsers())
    {
        if (it == user.getUserName() && this->games.find(user) == games.end())
        {
            this->games[this->user] = Game(gameId);
            gameId++;
            return this->games[this->user];
        }
    }
    throw std::runtime_error("Player not in the room");
}

void GameManager::deleteGame()
{
    if (this->games.find(user) != games.end())
        this->games.erase(user);
    else
        throw std::runtime_error("Player not in the room");
}

std::list<Question> GameManager::getTriviaQuestions()
{
    return this->db->getQuestions();
}