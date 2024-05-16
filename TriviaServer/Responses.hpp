#pragma once
#include <string>
#include <vector>
#include "RoomData.hpp"

typedef enum ResponseCode
{
	LOGIN_RC = 10,
	SIGNUP_RC = 20,
	LOGOUT_RC = 30,
	GET_ROOMS_RC = 40,
	GET_PLAYERS_IN_ROOM_RC = 50,
	JOIN_ROOM_RC = 60,
	CREATE_ROOM_RC = 70,
	GET_HIGH_SCORE_RC = 80,
	GET_PERSONAL_STATS_RC = 90,
	ERROR_RC = 255,
} ResponseCode;

typedef enum Status
{
	LOGIN_STATUS = 11,
	SIGNUP_STATUS = 21,
	LOGOUT_STATUS = 31,
	GET_ROOMS_STATUS = 41,
	GET_PLAYERS_IN_ROOM_STATUS = 51,
	JOIN_ROOM_STATUS = 61,
	CREATE_ROOM_STATUS = 71,
	GET_HIGH_SCORE_STATUS = 81,
	GET_PERSONAL_STATS_STATUS = 91
} Status;

typedef enum Errors
{
	LOGIN_ERROR = 15,
	SIGNUP_ERROR = 25,
	PASSWORD_WEAK = 26,
	LOGOUT_ERROR = 35,
	GET_ROOMS_ERROR = 45,
	GET_PLAYERS_IN_ROOM_ERROR = 55,
	JOIN_ROOM_ERROR = 65,
	CREATE_ROOM_ERROR = 75,
	GET_HIGH_SCORE_ERROR = 85,
	THERE_IS_NO_SCORES = 86,
	GET_PERSONAL_STATS_ERROR = 95
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

typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	std::string statistics;
} GetPersonalStatsResponse;