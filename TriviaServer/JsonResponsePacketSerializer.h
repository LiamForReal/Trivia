#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp"
#include "Responses.hpp"

class JsonResponsePacketSerializer
{
	public:
		static std::vector<unsigned char> serializeResponse(const ErrorResponse& errorResponse);
		static std::vector<unsigned char> serializeResponse(const LoginResponse& loginResponse);
		static std::vector<unsigned char> serializeResponse(const SignupResponse& signupResponse);
		static std::vector<unsigned char> serializeResponse(const LogoutResponse& logoutResponse);
		static std::vector<unsigned char> serializeResponse(const GetRoomsResponse& getRoomsResponse);
		static std::vector<unsigned char> serializeResponse(const GetPlayersInRoomResponse& getPlayerInRoomResponse);
		static std::vector<unsigned char> serializeResponse(const JoinRoomResponse& joinRoomResponse);
		static std::vector<unsigned char> serializeResponse(const CreateRoomResponse& createRoomResponse);
		static std::vector<unsigned char> serializeResponse(const GetHighScoreResponse& getHighScoreResponse);


};

