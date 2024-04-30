#pragma once
class UserStatistics
{
public:
	UserStatistics();
	UserStatistics(int numberOfGames, int numberOfCorrectAnswers, int numOfTotalAnswers, int AvrageTimeForAnswer);
	~UserStatistics();

	int getNumOfGames() const;
	int getNumOfCorrectAnswers() const;
	int getNumOfTotalAnswers() const;
	float getAvrageTimeForAnswer() const;

	void setNumOfGames(const int newNumOfGames);
	void setNumOfCorrectAnswers(const int newNumOfCorrectAnswers);
	void setNumOfTotalAnswers(const int newNumOfTotalAnswers);
	void setAvrageTimeForAnswer(const float newAvrageTimeForAnswer);

private:
	int _numberOfGames;
	int _numberOfCorrectAnswers;
	int _numOfTotalAnswers;
	float _avrageTimeForAnswer;
};

