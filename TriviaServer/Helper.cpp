#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "defines.hpp"

using std::string;

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(const SOCKET sc)
{
	std::string msg = getPartFromSocket(sc, 3, 0);

	if (msg == "")
		return 0;

	int res = std::atoi(msg.c_str());
	return  res;
}

unsigned int Helper::socketHasData(SOCKET socket) 
{
	char buf;
	unsigned int code = Helper::getStatusCodeFromSocket(socket);
	return code;
}

void Helper::send_update_message_to_client(const SOCKET sc, const string& file_content, const string& second_username, const string &all_users)
{
	//TRACE("all users: %s\n", all_users.c_str())
	const string code = std::to_string(MT_SERVER_UPDATE);
	const string current_file_size = getPaddedNumber(file_content.size(), 5);
	const string username_size = getPaddedNumber(second_username.size(), 2);
	const string all_users_size = getPaddedNumber(all_users.size(), 5);
	const string res = code + current_file_size + file_content + username_size + second_username + all_users_size + all_users;
	//TRACE("message: %s\n", res.c_str());
	sendData(sc, res);
}

// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return atoi(getPartFromSocket(sc, bytesNum, 0).c_str());
}

// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

void Helper::sendVector(const SOCKET sc, const std::vector<unsigned char>& vec)
{
	std::cout << "Sending...\n";
	const char* dataPtr = reinterpret_cast<const char*>(vec.data());
	int dataSize = static_cast<int>(vec.size());
	int totalBytesSent = 0;

	while (totalBytesSent < dataSize)
	{
		int bytesSent = send(sc, dataPtr + totalBytesSent, dataSize - totalBytesSent, 0);

		if (bytesSent == SOCKET_ERROR)
		{
			throw std::runtime_error("Error while sending message to client");
		}
		else if (bytesSent == 0)
		{
			std::cerr << "Connection closed by the client\n";
			throw std::runtime_error("Connection closed by the client");
		}

		totalBytesSent += bytesSent;
	}

	if (totalBytesSent != dataSize)
	{
		std::cerr << "Failed to send entire message to client\n";
		throw std::runtime_error("Failed to send entire message to client");
	}
}


// return string after padding zeros if necessary
string Helper::getPaddedNumber(const int num, const int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

unsigned int Helper::getStatusCodeFromSocket(const SOCKET sc)
{
	unsigned int value = 0;
	unsigned char* data = getUnsignedCharPartFromSocket(sc, STATUS_CODE_BYTES_LENGTH, 0);

	value = (value << 8) | static_cast<unsigned char>(data[0]);

	delete[] data;

	return value;
}

unsigned int Helper::getLengthPartFromSocket(const SOCKET sc)
{
	int i = 0;
	unsigned int value = 0;
	unsigned char* data = Helper::getUnsignedCharPartFromSocket(sc, MESSAGE_LENGTH_BYTES_LENGTH, 0); // Assuming getPartFromSocket returns the byte data as a string


	for (i = 0; i < MESSAGE_LENGTH_BYTES_LENGTH; i++)
	{
		value |= (static_cast<unsigned int>(data[i]) << (i * 8));
	}

	delete[] data;

	return value;
}

// recieve data from socket according byteSize
// this is private function
std::string Helper::getPartFromSocket(const SOCKET sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

// send data to socket
// this is private function
void Helper::sendData(const SOCKET sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string Helper::getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);
	delete[] data;
	return received;
}

unsigned char* Helper::getUnsignedCharPartFromSocket(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return nullptr;
	}

	unsigned char* data = new unsigned char[bytesNum];
	int res = recv(sc, reinterpret_cast<char*>(data), bytesNum, flags);

	if (res == SOCKET_ERROR)
	{
		std::string s = "Error while receiving from socket: ";
		s += std::to_string(sc);
		throw std::runtime_error(s);
	}
	else if (res != bytesNum)
	{
		// Handle incomplete data reception if needed
	}

	//data[bytesNum] = '\0';

	return data;
}