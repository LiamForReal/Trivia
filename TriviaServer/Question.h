#pragma once
#include "includes.hpp"

class Question
{
public:
	Question(string q, string ca, string wa1, string wa2, string wa3);
	Question(string q, string ca, string wa1, string wa2, string wa3, int id);
	~Question();

	string getQ() const;
	string getCA() const;
	string getWA1() const;
	string getWA2() const;
	string getWA3() const;
	int getId() const;

	void setId(const int newId);
	void setQ(const string& newQ);
	void setCA(const string& newCA);
	void setWA1(const string& newWA1);
	void setWA2(const string& newWA2);
	void setWA3(const string& newWA3);

private:
	string _question;
	string _correctAnswer;
	string _wrong1;
	string _wrong2;
	string _wrong3;
	int _id;
};

