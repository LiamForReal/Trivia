#include "GameManager.h"
#include <stdexcept>

int GameManager::gameId = 0;

GameManager::GameManager()
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

Game& GameManager::getGame(LoggedUser user)
{
    return std::ref(this->games[user]);
}

Game& GameManager::createGame(Room room, LoggedUser user)
{
    vector<string> users = room.getAllUsers();
    for (auto it = users.begin(); it != users.end(); it++)
    {
        this->games[user] = Game(gameId);
    }
    return std::ref(this->games[user]);
}

void GameManager::deleteGame(LoggedUser user)
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
void GameManager::setQuestionId(const int newQuestionId, LoggedUser user)
{
    this->games[user].setQuestionId(newQuestionId);
}
void GameManager::setAvrageTime(const float newAvrageTime, LoggedUser user)
{
    this->games[user].setavrageTime(newAvrageTime);
}