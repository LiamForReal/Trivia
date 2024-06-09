#include "Game.h"

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