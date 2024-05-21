#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& rhf, unsigned int roomId, LoggedUser member) : _rhf(rhf)
{
	this->roomId = roomId;
	this->Member = member;
}

RoomMemberRequestHandler::~RoomMemberRequestHandler() {}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return requestInfo.id == LEAVE_ROOM_RC || requestInfo.id == GET_ROOM_STATE_RC;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult rr = RequestResult();
	if (requestInfo.id == LEAVE_ROOM_RC)
	{
		LeaveRoomResponse lrr = LeaveRoomResponse();
		lrr.status = LEAVE_ROOM_STATUS;
		try
		{
			_rhf.getRoomManager().getRoom(roomId).removeUser(Member);
			rr.newHandler = _rhf.createRoomMemberRequestHandler(roomId, Member);
		}
		catch (std::runtime_error& e)
		{
			lrr.status = LEAVE_ROOM_ERROR;
			std::cout << e.what() << std::endl;
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lrr);
	}
	else if (requestInfo.id == GET_ROOM_STATE_RC)
	{

	}
	else throw std::runtime_error("invalid request id [login request handler]");
	return rr;
}