#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory rhf, LoggedUser user, unsigned int roomId) : _rhf(rhf), _user(user)
{
	_roomId = roomId;
}
GameRequestHandler::~GameRequestHandler() {}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{

	return requestInfo.id == GET_GAME_RESULTS_RC || requestInfo.id == SUBMIT_ANSWER_RC || requestInfo.id == GET_QUESTION_RC || requestInfo.id == LEAVE_GAME_RC;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult rr = RequestResult();
	PlayerResults playerResults;
	if (requestInfo.id == GET_GAME_RESULTS_RC)
	{
		GetGameResultsResponse ggr = GetGameResultsResponse();
		ggr.status = GET_GAME_RESULTS_STATUS;
		rr.newHandler = _rhf.createMenuRequestHandler(_user);
		try
		{
			vector<string> users = _rhf.getRoomManager().getRoom(_roomId).getAllUsers();
			for (auto it = users.begin(); it != users.end(); ++it)
			{
				playerResults = PlayerResults(*it, (unsigned int)(std::stoi(_rhf.getStatisticsManager().getUserStatistics(*it)[1])),
					(unsigned int)(std::stoi(_rhf.getStatisticsManager().getUserStatistics(*it)[2])), 
					(unsigned int)(std::stoi(_rhf.getStatisticsManager().getUserStatistics(*it)[3])));
				ggr.results.push_back(playerResults);
			}
		}
		catch (std::runtime_error& e)
		{
			ggr.status = GET_GAME_RESULTS_ERROR;
			rr.newHandler = _rhf.createGameRequestHandler(_user, _roomId);
			std::cout << e.what() << std::endl;
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(ggr);
	}
	else if (requestInfo.id == SUBMIT_ANSWER_RC)
	{

	}
	else if (requestInfo.id == GET_QUESTION_RC)
	{
		GetQuestionResponse gqr = GetQuestionResponse();
		gqr.status = GET_QUESTION_STATUS;
		try
		{
			list<Question> questions = _rhf.getGameManager().getTriviaQuestions();
			for (auto it = questions.begin(); it != questions.end(); it++)
			{
				if (it->getId() == questionId)
				{
					gqr.question = it->getQ();
					gqr.answers[0] = it->getCA();
					gqr.answers[1] = it->getWA1();
					gqr.answers[2] = it->getWA2();
					gqr.answers[3] = it->getWA3();
					break;
				}
			}
			questionId = (std::rand() % (UPPER_BOND - LOWER_BOND + 1)) + LOWER_BOND;
		}
		catch (std::runtime_error& e)
		{
			gqr.status = GET_QUESTION_ERROR;
			std::cout << e.what() << std::endl;
		}
		rr.newHandler = _rhf.createGameRequestHandler(_user, _roomId);
		std::cout << "DEBUG: response code " << gqr.status << std::endl;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gqr);
	}
	else if (requestInfo.id == LEAVE_GAME_RC)
	{
		LeaveGameResponse lgr = LeaveGameResponse();
		lgr.status = LEAVE_GAME_STATUS;
		rr.newHandler = _rhf.createMenuRequestHandler(_user);
		try
		{
			_rhf.getRoomManager().getRoom(_roomId).removeUser(_user);
		}
		catch (std::runtime_error& e)
		{
			lgr.status = LEAVE_GAME_ERROR;
			rr.newHandler = _rhf.createGameRequestHandler(_user, _roomId);
			std::cout << e.what() << std::endl;
		}
		std::cout << "DEBUG: response code " << lgr.status << std::endl;
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lgr);
	}
	else throw std::runtime_error("invalid request id [game request handler]");
	return rr;
}