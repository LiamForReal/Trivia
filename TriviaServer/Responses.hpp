#pragma once
#include <string>
#include <vector>
#include "RoomData.hpp"

typedef enum ResponseCode
{
	LOGIN_RC = 100,
	SIGNUP_RC = 200,
	LOGOUT_RC = 300,
	GET_ROOMS_RC = 400,
	GET_PLAYERS_IN_ROOM_RC = 500,
	JOIN_ROOM_RC = 600,
	CREATE_ROOM_RC = 700,
	GET_HIGH_SCORE_RC = 800,
	ERROR_RC = 9999,
} ResponseCode;

typedef enum Status
{
	LOGIN_STATUS = 101,
	SIGNUP_STATUS = 201,
	LOGOUT_STATUS = 301,
	GET_ROOMS_STATUS = 401,
	GET_PLAYERS_IN_ROOM_STATUS = 501,
	JOIN_ROOM_STATUS = 601,
	CREATE_ROOM_STATUS = 701,
	GET_HIGH_SCORE_STATUS = 801,
} Status;

typedef enum Errors
{
	LOGIN_ERROR = 105,
	SIGNUP_ERROR = 205,
	PASSWORD_WEAK = 210,
	LOGOUT_ERROR = 305,
	GET_ROOMS_ERROR = 405,
	GET_PLAYERS_IN_ROOM_ERROR = 505,
	JOIN_ROOM_ERROR = 605,
	CREATE_ROOM_ERROR = 705,
	GET_HIGH_SCORE_ERROR = 805,

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
	unsigned int status;
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