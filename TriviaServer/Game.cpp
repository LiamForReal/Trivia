#include "Game.h"

Game::Game(int id)
{
	this->avrageTimePerAnswer = 0.0f;
	this->questionId = -1;
	this->gameId = id;
}

Game::Game()
{
	this->avrageTimePerAnswer = 0.0f;
	this->questionId = -1;
	this->gameId = -1;
}

Game::~Game() {}

int Game::getQuestionId() const 
{
	return this->questionId;
}

float Game::getAvrageTime() const
{
	return this->avrageTimePerAnswer;
}

void Game::setQuestionId(const int questionId)
{
	this->questionId = questionId;
}

void Game::setavrageTime(const float avrageTime)
{
	this->avrageTimePerAnswer = avrageTime;
}

void Game::setGameId(const int gameId)
{
	this->gameId = gameId;
}

int Game::getGameId() const
{
	return this->gameId;
}

bool Game::operator==(const Game& other) const
{
	return  this->avrageTimePerAnswer == other.avrageTimePerAnswer && this->questionId == this->questionId;
}

Game& Game::operator=(const Game& other)
{
	if (nullptr == &other || this == &other)
	{
		return *this;
	}

	this->avrageTimePerAnswer = other.avrageTimePerAnswer;
	this->questionId = other.questionId;
	return *this;
}