#pragma once
#include "json.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
#include "Requests.hpp"

class JsonRequestPacketDeserializer
{
	public:
		static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);
		static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);
		static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const std::vector<unsigned char>& buffer);
		static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer);
		static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer);
		static SubmitAnswerRequest deserializeSubmitAnswerRequest(const std::vector<unsigned char>& buffer);
};

