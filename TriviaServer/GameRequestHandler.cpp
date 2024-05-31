#include "GameRequestHandler.h"

std::map<unsigned int, std::vector<Question>> GameRequestHandler::roomsQuestions;

GameRequestHandler::GameRequestHandler(RequestHandlerFactory rhf, LoggedUser user, unsigned int roomId) : _rhf(rhf), _user(user)
{
	_roomId = roomId;
	currentQuestion = 0;
	randQuestionsToRoom();
}

GameRequestHandler::~GameRequestHandler() {}

void GameRequestHandler::randQuestionsToRoom() 
{
	if (this->roomsQuestions[_roomId].size() > 0)
		return;

	std::srand(std::time(0));

	std::vector<Question> questions;
	unsigned int numOfQuestions = _rhf.getRoomManager().getRoom(_roomId).getMetadata().numOfQuestionsInGame;
	std::list<Question> questionsList = _rhf.getGameManager().getTriviaQuestions();

	if (questionsList.size() < numOfQuestions) {
		throw std::runtime_error("Not enough questions available");
	}

	while (questions.size() < numOfQuestions) {
		int randIndex = std::rand() % questionsList.size();

		auto it = questionsList.begin();
		std::advance(it, randIndex);

		if (std::find(questions.begin(), questions.end(), *it) == questions.end()) {
			questions.push_back(*it);
		}
	}
	this->roomsQuestions[_roomId] = questions;
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{

	return requestInfo.id == GET_GAME_RESULTS_RC || requestInfo.id == SUBMIT_ANSWER_RC || requestInfo.id == GET_QUESTION_RC || requestInfo.id == LEAVE_GAME_RC;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult rr = RequestResult();
	if (requestInfo.id == GET_GAME_RESULTS_RC)
	{
		PlayerResults playerResults;
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
		if (ggr.status == GET_GAME_RESULTS_STATUS)
			if(this->roomsQuestions.find(_roomId) != this->roomsQuestions.end() && this->roomsQuestions.size() != 0)
				this->roomsQuestions[_roomId].clear();
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(ggr);
	}
	else if (requestInfo.id == SUBMIT_ANSWER_RC)
	{
		SubmitAnswerRequest sar = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
		SubmitAnswerResponse sarr = SubmitAnswerResponse();
		bool isCorrect = false;
		try
		{
			if (currentQuestion >= this->roomsQuestions[_roomId].size())
				throw std::runtime_error("question out of vectors bounds");
			if (sar.answer == this->roomsQuestions[_roomId][currentQuestion].getCA())
			{
				sarr.status = SUBMIT_ANSWER_CORRECT;
				isCorrect = true;
			}
			else sarr.status = SUBMIT_ANSWER_WRONG;
			QuestionStatistics q = QuestionStatistics(this->_rhf.getGameManager().getGame(_user), _user.getUserName(), isCorrect, sar.answer);
			this->_rhf.getStatisticsManager().addNewQuestionStatistics(q);
			currentQuestion++;
		}
		catch (std::runtime_error& e)
		{
			sarr.status = SUBMIT_ANSWER_ERROR;
			std::cout << e.what() << std::endl;
		}
		rr.newHandler = _rhf.createGameRequestHandler(_user, _roomId);
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(sarr);
	}
	else if (requestInfo.id == GET_QUESTION_RC)
	{
		GetQuestionResponse gqr = GetQuestionResponse();
		gqr.status = GET_QUESTION_STATUS;
		try
		{
			if (currentQuestion >= this->roomsQuestions[_roomId].size())
			{
				gqr.status = GET_QUESTION_ALL_QUESTIONS_ALREADY_ASKED;
				throw std::runtime_error("question out of vectors bounds");
			}
			gqr.question = this->roomsQuestions[_roomId][currentQuestion].getQ();
			gqr.answers[0] = this->roomsQuestions[_roomId][currentQuestion].getCA();
			gqr.answers[1] = this->roomsQuestions[_roomId][currentQuestion].getWA1();
			gqr.answers[2] = this->roomsQuestions[_roomId][currentQuestion].getWA2();
			gqr.answers[3] = this->roomsQuestions[_roomId][currentQuestion].getWA3();
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