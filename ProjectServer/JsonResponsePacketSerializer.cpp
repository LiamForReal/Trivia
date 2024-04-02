#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

#define INIT_VEC_LEN 5
#define BYTES_TO_COPY 4

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	std::vector<unsigned char> vec(INIT_VEC_LEN);
	// Add Response Code
	vec.push_back((unsigned char)(ERROR_RC));

	json erJson = {
		{"message", errorResponse.message},
	};

	//size_t len = length of json;
	//std::memcpy(vec.data(), &len, BYTES_TO_COPY);


	return vec;
}
