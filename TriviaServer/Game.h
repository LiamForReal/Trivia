#pragma once
#include "includes.hpp"
class Game
{
public:
	Game();
	~Game();

    Game(const Game& other) :
        avrageTimePerAnswer(other.avrageTimePerAnswer),
        questionId(other.questionId),
        gameId(other.gameId)
    {
    }

    // Assignment operator
    Game& operator=(const Game& other)
    {
        if (this == &other)
            return *this; // Handle self-assignment

        // Copy data members
        avrageTimePerAnswer = other.avrageTimePerAnswer;
        questionId = other.questionId;
        gameId = other.gameId;

        return *this;
    }

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

