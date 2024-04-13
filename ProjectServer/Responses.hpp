#pragma once
#include <string>

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