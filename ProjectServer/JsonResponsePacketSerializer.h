#pragma once
#include <vector>
#include "json.hpp"

class JsonResponsePacketSerializer
{
	public:
		static std::vector<unsigned char> serializeResponse();
};

