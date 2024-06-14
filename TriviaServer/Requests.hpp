#pragma once
#include <string>

typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionsCount;
	unsigned int answerTimeout;
	bool isMatchMake;
} CreateRoomRequest;

typedef struct SubmitAnswerRequest
{
	std::string answer;
} SubmitAnswerRequest;

typedef struct AddNewQuestionRequest
{
	std::string question;
	std::string correctAnswer;
	std::string wrongAnswer1;
	std::string wrongAnswer2;
	std::string wrongAnswer3;
} AddNewQuestionRequest;