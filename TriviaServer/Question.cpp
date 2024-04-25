#include "Question.h"

Question::Question(string q, string ca, string wa1, string wa2, string wa3)
{
	this->_question = q;
	this->_correctAnswer = ca;
	this->_wrong1 = wa1;
	this->_wrong2 = wa2;
	this->_wrong3 = wa3;
}

Question::~Question() {}

string Question::getQ() const
{
	return this->_question;
}

string Question::getCA() const
{
	return this->_correctAnswer;
}
string Question::getWA1() const
{
	return this->_wrong1;
}
string Question::getWA2() const
{
	return this->_wrong2;
}
string Question::getWA3() const
{
	return this->_wrong3;
}

void Question::setQ(const string& newQ)
{
	this->_question = newQ;
}
void Question::setCA(const string& newCA)
{
	this->_correctAnswer = newCA;
}
void Question::setWA1(const string& newWA1)
{
	this->_wrong1 = newWA1;
}
void Question::setWA2(const string& newWA2)
{
	this->_wrong2 = newWA2;
}

void Question::setWA3(const string& newWA3)
{
	this->_wrong3 = newWA3;
}