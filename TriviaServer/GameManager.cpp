#include "GameManager.h"
#include <stdexcept>

GameManager::GameManager()
{
    this->gameId = 1;
    db = new SqliteDataBase();
    this->games = std::map<LoggedUser, Game>();
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

Game& GameManager::createGame(Room room)
{
    vector<string> users = room.getAllUsers();
    for (auto it = users.begin(); it != users.end(); it++)
    {
        this->games[*it] = Game();
        this->games[*it].setGameId(this->gameId);
    }
    gameId++;
    return std::ref(this->games[users[0]]);
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