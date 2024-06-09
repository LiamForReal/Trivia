#pragma once
#include "includes.hpp"
class Game
{
public:
	Game();
	~Game();

	int getQuestionId() const;
	int getGameId() const;
	float getAvrageTime() const;

	void setGameId(const int gameId);
	void setQuestionId(const int questionId);
	void setavrageTime(const float avrageTime);

private:
	int gameId;
	int questionId;
	float avrageTimePerAnswer;
};

