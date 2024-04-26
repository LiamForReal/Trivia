#pragma once
#include <string>
#include <vector>
#include "RoomData.hpp"

typedef enum ResponseCode
{
	LOGIN_RC = 100,
	SIGNUP_RC = 200,
	ERROR_RC = 500,
} ResponseCode;

typedef enum Status
{
	LOGIN_STATUS = 101,
	SIGNUP_STATUS = 201,
} Status;

typedef enum Errors
{
	LOGIN_ERROR = 105,
	SIGNUP_ERROR = 205,
	PASSWORD_WEAK = 210,
} Errors;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

typedef struct LoginResponse
{
	unsigned int status;
};

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

typedef struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
} GetHighScoreResponse;