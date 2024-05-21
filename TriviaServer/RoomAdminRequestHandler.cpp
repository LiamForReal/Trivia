#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId, LoggedUser owner) : _rhf(rhf)
{
	this->roomId = roomId;
	this->Owner = owner;
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
		rr.newHandler = _rhf.createMenuRequestHandler(Owner);
		try
		{
			vector<string> usersInRoom = _rhf.getRoomManager().getRoom(roomId).getAllUsers();
			for (int i = 0; i < usersInRoom.size(); i++)
			{
				_rhf.getRoomManager().getRoom(roomId).removeUser(usersInRoom[i]);
				//TODO
			}
			//_rhf.getRoomManager().deleteRoom(roomId);
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			crr.status = CLOSE_ROOM_ERROR;
			rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId, Owner);
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(crr);
		rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId, Owner);
	}
	else if (requestInfo.id == START_GAME_RC)
	{
		//TODO - discuss on this
	}
	else if (requestInfo.id == GET_ROOM_STATE_RC)
	{
		GetRoomStateResponse grsr = GetRoomStateResponse(); //TO CHANGE
		if (_rhf.getRoomManager().getRoom(roomId).getMetadata().isActive == 1)
			grsr.status = GET_ROOM_STATE_SERVER_STATUS;
		else grsr.status = GET_ROOM_STATE_SERVER_ERROR;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(grsr);
		rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId, Owner);
	}
	else  throw std::runtime_error("invalid request id [Room admin request handler]");
	return rr;
}