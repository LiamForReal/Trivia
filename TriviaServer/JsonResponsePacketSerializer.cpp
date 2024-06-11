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
	vec[0] = ((unsigned char)(loginResponse.status));

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
	vec[0] = ((unsigned char)(signupResponse.status));

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
	vec[0] = ((unsigned char)(logoutResponse.status));

	unsigned int len = 0;

	json lrJson = {
		{"status", logoutResponse.status},
	};

	std::string lrJsonStr = lrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(lrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), lrJsonStr.begin(), lrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& getRoomsResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getRoomsResponse.status));

	unsigned int len = 0;

	std::vector<json> roomsDataVec;
	json temp;

	for (auto it = getRoomsResponse.rooms.begin(); it != getRoomsResponse.rooms.end(); it++)
	{
		const_cast<RoomData&>((*it)).to_json(temp, (*it));
		roomsDataVec.push_back(temp);
	}

	json grrJson = {
		{"status", getRoomsResponse.status},
		{"rooms", json(roomsDataVec)},
	};

	roomsDataVec.clear();
	temp.clear();

	std::string grrJsonStr = grrJson.dump();

	std::cout << "[Json Structs and Vecs] DEBUG: " << grrJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(grrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), grrJsonStr.begin(), grrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayerInRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getPlayerInRoomResponse.status));

	unsigned int len = 0;

	json gpirrJson = {
		{"status", getPlayerInRoomResponse.status},
		{"players", json(getPlayerInRoomResponse.players)},
	};

	std::string gpirrJsonStr = gpirrJson.dump();

	std::cout << "[Json Strings and Vecs] DEBUG: " << gpirrJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(gpirrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), gpirrJsonStr.begin(), gpirrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& joinRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(joinRoomResponse.status));

	unsigned int len = 0;

	json jrrJson = {
		{"status", joinRoomResponse.status},
	};

	std::string jrrJsonStr = jrrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(jrrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), jrrJsonStr.begin(), jrrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& createRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(createRoomResponse.status));

	unsigned int len = 0;

	json crrJson = {
		{"status", createRoomResponse.status},
	};

	std::string crrJsonStr = crrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(crrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), crrJsonStr.begin(), crrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& getHighScoreResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getHighScoreResponse.status));

	unsigned int len = 0;

	json ghsrJson = {
		{"statistics", json(getHighScoreResponse.statistics)},
		{"status", getHighScoreResponse.status},
	};

	std::string ghsrJsonStr = ghsrJson.dump();

	std::cout << "[Json Strings and Vecs] DEBUG: " << ghsrJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(ghsrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), ghsrJsonStr.begin(), ghsrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getPersonalStatsResponse.status));

	unsigned int len = 0;

	json gpsrJson = {
		{"statistics", getPersonalStatsResponse.statistics},
		{"status", getPersonalStatsResponse.status},
	};

	std::string gpsrJsonStr = gpsrJson.dump();

	std::cout << "[Json Strings] DEBUG: " << gpsrJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(gpsrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), gpsrJsonStr.begin(), gpsrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& closeRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(closeRoomResponse.status));

	unsigned int len = 0;

	json crrJson = {
		{"status", closeRoomResponse.status},
	};

	std::string crrJsonStr = crrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(crrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), crrJsonStr.begin(), crrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& startGameResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(startGameResponse.status));

	unsigned int len = 0;

	json sgrJson = {
		{"status", startGameResponse.status},
	};

	std::string sgrJsonStr = sgrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(sgrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), sgrJsonStr.begin(), sgrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& getRoomStateResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getRoomStateResponse.status));

	unsigned int len = 0;

	json grsrJson = {
		{"status", getRoomStateResponse.status},
		{"hasGameBegun", getRoomStateResponse.status},
		{"players", json(getRoomStateResponse.players)},
		{"questionCount", getRoomStateResponse.questionCount},
		{"answerTimeout", getRoomStateResponse.answerTimeout}
	};

	std::string grsrJsonStr = grsrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(grsrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), grsrJsonStr.begin(), grsrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& leaveRoomResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(leaveRoomResponse.status));

	unsigned int len = 0;

	json lrrJson = {
		{"status", leaveRoomResponse.status},
	};

	std::string lrrJsonStr = lrrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(lrrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), lrrJsonStr.begin(), lrrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse& getGameResultsResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getGameResultsResponse.status));

	unsigned int len = 0;

	std::vector<json> resultsVec;
	json temp;

	for (auto it = getGameResultsResponse.results.begin(); it != getGameResultsResponse.results.end(); it++)
	{
		const_cast<PlayerResults&>((*it)).to_json(temp, (*it));
		resultsVec.push_back(temp);
	}

	json ggrrJson = {
		{"status", getGameResultsResponse.status},
		{"results", json(resultsVec)},
	};

	resultsVec.clear();
	temp.clear();

	std::string ggrrJsonStr = ggrrJson.dump();

	std::cout << "[Json Structs and Vecs] DEBUG: " << ggrrJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(ggrrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), ggrrJsonStr.begin(), ggrrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& submitAnswerResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(submitAnswerResponse.status));

	unsigned int len = 0;

	json sarJson = {
		{"status", submitAnswerResponse.status}
	};

	std::string sarJsonStr = sarJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(sarJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), sarJsonStr.begin(), sarJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& getQuestionResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(getQuestionResponse.status));

	unsigned int len = 0;

	json gqrJson = {
		{"status", getQuestionResponse.status},
		{"question", getQuestionResponse.question},
		{"answers", json(getQuestionResponse.answers)}
	};

	std::string gqrJsonStr = gqrJson.dump();

	std::cout << "[QUESTION DATA DEBUG:] " << gqrJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(gqrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), gqrJsonStr.begin(), gqrJsonStr.end());

	return vec;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse& leaveGameResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_SIZE);
	// Add Response Code
	vec[0] = ((unsigned char)(leaveGameResponse.status));

	unsigned int len = 0;

	json lgrJson = {
		{"status", leaveGameResponse.status},
	};

	std::string lgrJsonStr = lgrJson.dump();

	// Insert Message Length Into Vector
	len = (unsigned int)(lgrJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data() + INC, &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), lgrJsonStr.begin(), lgrJsonStr.end());

	return vec;
}
