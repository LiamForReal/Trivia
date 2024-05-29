#include "Game.h"

Game::Game()
{
	this->avrageTimePerAnswer = 0.0f;
	this->currentTrueAnswers = 0;
	this->currentWrongAnswers = 0;
	this->questionId = -1;
}

Game::~Game() {}

int Game::getQuestionId() const 
{
	return this->questionId;
}

int Game::getTrueAns() const
{
	return this->currentTrueAnswers;
}

int Game::getWrongAns() const
{
	return this->currentWrongAnswers;
}

float Game::getAvrageTime() const
{
	return this->avrageTimePerAnswer;
}

void Game::setQuestionId(const int questionId)
{
	this->questionId = questionId;
}

void Game::incTrueAns()
{
	this->currentTrueAnswers++;
}
void Game::incWrongAns()
{
	this->currentWrongAnswers++;
}
void Game::setTrueAns(const int trueAns)
{
	this->currentTrueAnswers = trueAns;
}
void Game::setWrongAns(const int wrongAns)
{
	this->currentWrongAnswers = wrongAns;
}
void Game::setavrageTime(const float avrageTime)
{
	this->avrageTimePerAnswer = avrageTime;
}

bool Game::operator==(const Game& other) const
{
	return  this->avrageTimePerAnswer == other.avrageTimePerAnswer && this->currentTrueAnswers == other.currentTrueAnswers && 
		this->currentWrongAnswers == other.currentWrongAnswers && this->questionId == this->questionId;
}

Game& Game::operator=(const Game& other)
{
	if (nullptr == &other || this == &other)
	{
		return *this;
	}

	this->avrageTimePerAnswer = other.avrageTimePerAnswer;
	this->currentTrueAnswers = other.currentTrueAnswers;
	this->currentWrongAnswers = other.currentWrongAnswers;
	this->questionId = other.questionId;
	return *this;
}