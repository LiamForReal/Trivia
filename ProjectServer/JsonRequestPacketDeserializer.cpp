#include "JsonRequestPacketDeserializer.h"
#include <iostream> // for debug

#define INC 1
#define BYTES_TO_COPY 4

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
	LoginRequest lr;

	unsigned int len = 0;

	memcpy(&len, buffer.data() + INC, BYTES_TO_COPY);
	

	std::cout << len << std::endl;

	return lr;
}
