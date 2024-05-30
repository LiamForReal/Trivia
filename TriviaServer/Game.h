#pragma once
class Game
{
public:
	Game(int id);
	Game();
	~Game();

	int getQuestionId() const;
	int getTrueAns() const;
	int getWrongAns() const;
	int getGameId() const;
	float getAvrageTime() const;

	void setQuestionId(const int questionId);
	void incTrueAns();
	void incWrongAns();
	void setGameId(const int gameId);
	void setTrueAns(const int trueAns);
	void setWrongAns(const int wrongAns);
	void setavrageTime(const float avrageTime);
	bool operator==(const Game& other) const;
	Game& operator=(const Game& other);
private:
	int gameId;
	int questionId;
	int currentTrueAnswers;
	int currentWrongAnswers;
	float avrageTimePerAnswer;
};

