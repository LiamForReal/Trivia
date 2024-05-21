#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId) : _rhf(rhf) 
{
	this->roomId = roomId;
}

RoomAdminRequestHandler::~RoomAdminRequestHandler() {}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return requestInfo.id == CLOSE_ROOM_RC || requestInfo.id == START_GAME_RC || requestInfo.id == GET_ROOM_STATE_RC;
}
RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult rr = RequestResult();
	if (requestInfo.id == CLOSE_ROOM_RC)
	{
		CloseRoomResponse crr = CloseRoomResponse();
		crr.status = CLOSE_ROOM_STATUS;
		try
		{
			vector<string> usersInRoom = _rhf.getRoomManager().getRoom(roomId).getAllUsers();
			//not done yet
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			crr.status = CLOSE_ROOM_ERROR;
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(crr);
		rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId);
	}
	else if (requestInfo.id == START_GAME_RC)
	{
		//TODO - discuss on this
	}
	else if (requestInfo.id == GET_ROOM_STATE_RC)
	{
		GetRoomStateResponse grsr = GetRoomStateResponse();
		if (_rhf.getRoomManager().getRoom(roomId).getMetadata().isActive == 1)
			grsr.status = GET_ROOM_STATE_STATUS;
		else grsr.status = GET_ROOM_STATE_ERROR;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(grsr);
		rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId);
	}
	else  throw std::runtime_error("invalid request id [Room admin request handler]");
	return rr;
}