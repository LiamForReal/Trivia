#pragma once
class Game
{
public:
	Game();
	~Game();

	int getQuestionId() const;
	int getTrueAns() const;
	int getWrongAns() const;
	float getAvrageTime() const;

	void setQuestionId(const int questionId);
	void incTrueAns();
	void incWrongAns();
	void setTrueAns(const int trueAns);
	void setWrongAns(const int wrongAns);
	void setavrageTime(const float avrageTime);
	bool operator==(const Game& other) const;
	Game& operator=(const Game& other);
private:
	int questionId;
	int currentTrueAnswers;
	int currentWrongAnswers;
	float avrageTimePerAnswer;
};

