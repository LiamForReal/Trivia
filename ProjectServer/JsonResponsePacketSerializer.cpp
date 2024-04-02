#include "JsonResponsePacketSerializer.h"
#include <iostream> // for debug

using json = nlohmann::json;

#define INIT_VEC_LEN 5
#define BYTES_TO_COPY 4

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_LEN);
	// Add Response Code
	vec.push_back((unsigned char)(ERROR_RC));

	unsigned int len = 0;

	json erJson = {
		{"message", errorResponse.message},
	};

	std::string erJsonStr = erJson.dump();
	// std::cout << erJsonStr << std::endl;

	// Insert Message Length Into Vector
	len = (unsigned int)(erJsonStr.size()); // possible lose of data for 64 bits.
	std::memcpy(vec.data(), &len, BYTES_TO_COPY);

	// Insert Message Into Vector
	vec.insert(vec.end(), erJsonStr.begin(), erJsonStr.end());

	return vec;
}
