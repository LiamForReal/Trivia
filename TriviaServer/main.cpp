#pragma comment (lib, "ws2_32.lib")
#include "SocketTools.h"
#include "WSAInitializer.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <fstream>

// In a lot of places in the code we pass to function constant reference (const Bla&)
// to an object and not the object itself, 

void run_server();

void run_json_tests();

void run_json_test_v2(void);

void run_json_test_v4(void); // tests for Version 4.0.0

int main()
{
	run_server();
	//run_json_tests();
	//run_json_test_v2();
	//run_json_test_v4();
}

void run_server()
{
	// Q: why is this try necessarily ?
	// A: we want to know what happened that made the server crush
	try
	{

		TRACE("Starting...");
		// NOTICE at the end of this block the WSA will be closed 
		WSAInitializer wsa_init;
		SocketTools md_server;
		md_server.serve();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
}

void run_json_tests(void)
{
	ErrorResponse er = {"ERORR",};

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(er);
	
	// test print
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
	}
	std::cout << std::endl;
	try
	{
		JsonRequestPacketDeserializer::deserializeLoginRequest(vec);
	}
	catch (...)
	{
		std::cout << "json error..." << std::endl;
	}

	vec.clear();
}

void run_json_test_v2(void)
{
	RoomData rd = {
		1,
		"Gavriel's Room",
		5,
		10,
		30,
		1
	};

	RoomData rd1 = {
	2,
	"Liam's Room",
	7,
	10,
	20,
	1
	};

	RoomData rd2 = {
	3,
	"Users's Room",
	5,
	80,
	60,
	0
	};

	std::vector<RoomData> vec;
	vec.push_back(rd);
	vec.push_back(rd1);
	vec.push_back(rd2);

	GetRoomsResponse grr = {
		500, vec
	};

	try
	{
		JsonResponsePacketSerializer::serializeResponse(grr);
	}
	catch (...)
	{
		std::cout << "json error..." << std::endl;
	}

	vec.clear();
}