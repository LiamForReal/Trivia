#include "JsonResponsePacketSerializer.h"
#include <iostream> // for debug

#include "defines.hpp"

using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(ERROR_RC));

	unsigned int len = 0;

	json erJson = {
		{"message", errorResponse.message},
	};

	std::string erJsonStr = erJson.dump();
	//std::cout << erJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(erJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	vec.resize(INIT_VEC_SIZE + len);

	// Insert Message Into Vector
	vec.insert(vec.end(), erJsonStr.begin(), erJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(LOGIN_RC));

	unsigned int len = 0;

	json lrJson = {
		{"status", loginResponse.status},
	};

	std::string lrJsonStr = lrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(lrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), lrJsonStr.begin(), lrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(SIGNUP_RC));

	unsigned int len = 0;

	json srJson = {
		{"status", signupResponse.status},
	};

	std::string srJsonStr = srJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(srJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), srJsonStr.begin(), srJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(LOGOUT_RC));

	unsigned int len = 0;

	json srJson = {
		{"status", logoutResponse.status},
	};

	std::string srJsonStr = srJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(srJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), srJsonStr.begin(), srJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& getRoomsResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(GET_ROOMS_RC));

	unsigned int len = 0;

	std::vector<json> roomsDataVec;
	json temp;

	for (auto it = getRoomsResponse.rooms.begin(); it != getRoomsResponse.rooms.end(); it++)
	{
		const_cast<RoomData&>((*it)).to_json(temp, (*it));
		roomsDataVec.push_back(temp);
	}

	json srJson = {
		{"status", getRoomsResponse.status},
		{"rooms", json(roomsDataVec)},
	};

	roomsDataVec.clear();
	temp.clear();

	std::string srJsonStr = srJson.dump();

	std::cout << "[Json Structs and Vecs] DEBUG: " << srJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(srJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), srJsonStr.begin(), srJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayerInRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(GET_PLAYERS_IN_ROOM_RC));

	unsigned int len = 0;

	json srJson = {
		{"players", json(getPlayerInRoomResponse.players)},
	};

	std::string srJsonStr = srJson.dump();

	std::cout << "[Json Strings and Vecs] DEBUG: " << srJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(srJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), srJsonStr.begin(), srJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& joinRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(JOIN_ROOM_RC));

	unsigned int len = 0;

	json srJson = {
		{"status", joinRoomResponse.status},
	};

	std::string srJsonStr = srJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(srJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), srJsonStr.begin(), srJsonStr.end());

	return vec;
}




