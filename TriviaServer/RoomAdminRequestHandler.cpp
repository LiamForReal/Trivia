#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId, LoggedUser owner) : _rhf(rhf), Owner(owner)
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
		rr.newHandler = _rhf.createMenuRequestHandler(Owner);
		try
		{
			_rhf.getRoomManager().deleteRoom(roomId);
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			crr.status = CLOSE_ROOM_ERROR;
			rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId, Owner);
		}
		std::cout << "DEBUG: response code " << crr.status << std::endl;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(crr);
	}
	else if (requestInfo.id == START_GAME_RC)
	{
		StartGameResponse sgr = StartGameResponse();
		_rhf.getRoomManager().getRoom(roomId).setRoomStatus(1);
		sgr.status = START_GAME_STATUS;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(sgr);
		std::cout << "DEBUG: response code " << sgr.status << std::endl;
		rr.newHandler = _rhf.createGameRequestHandler(Owner, roomId);
	}
	else if (requestInfo.id == GET_ROOM_STATE_RC)
	{
		GetRoomStateResponse grsr = GetRoomStateResponse();
		grsr.players = std::vector<std::string>();
		std::vector<std::string> usersInRoom = _rhf.getRoomManager().getRoom(roomId).getAllUsers();
		std::copy(usersInRoom.begin(), usersInRoom.end(), std::back_inserter(grsr.players));
		if (_rhf.getRoomManager().getRoom(roomId).getMetadata().isActive == 1)
			grsr.status = GET_ROOM_STATE_SERVER_STATUS;
		else grsr.status = GET_ROOM_STATE_SERVER_ERROR;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(grsr);
		rr.newHandler = _rhf.createRoomAdminRequestHandler(roomId, Owner);
	}
	else throw std::runtime_error("invalid request id [Room admin request handler]");
	return rr;
}