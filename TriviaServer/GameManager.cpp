#include "GameManager.h"
#include <stdexcept>

int GameManager::gameId = 1;

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

Game& GameManager::createGame(Room room)
{
    vector<string> users = room.getAllUsers();
    auto it = users.begin();
    bool flag = false;
    Game game;
    for (it = users.begin(); it != users.end(); it++)
    {
        if (this->games.find(*it) == this->games.end())
        {
            game = Game();
            game.setGameId(gameId);
            this->games[*it] = game;
            flag = true;
        } 
    }

    if (flag)
    {
        gameId++;
        return std::ref(this->games[room.getAllUsers()[0]]);
    }
    throw std::runtime_error("cant create geme for room!");
       
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