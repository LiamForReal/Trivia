#include "GameRequestHandler.h"

map<unsigned int, std::pair<vector<Question>, std::map<LoggedUser, int>>> GameRequestHandler::roomsQuestions;
std::map<LoggedUser, std::chrono::high_resolution_clock::time_point> GameRequestHandler::avrageTime;
map<unsigned int, Room> GameRequestHandler::getStatsRoom;

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& rhf, LoggedUser user, unsigned int roomId) : _rhf(rhf), _user(user)
{
	_roomId = roomId;	
	randQuestionsToRoom();
}

GameRequestHandler::~GameRequestHandler() {}

void GameRequestHandler::randQuestionsToRoom() 
{
	if (this->roomsQuestions[_roomId].first.size() > 0)
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
	this->roomsQuestions[_roomId].first = questions; 
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{

	return requestInfo.id == GET_GAME_RESULTS_RC || requestInfo.id == SUBMIT_ANSWER_RC || requestInfo.id == GET_QUESTION_RC || requestInfo.id == LEAVE_GAME_RC;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult rr = RequestResult();
	int currentQuestion = this->roomsQuestions[_roomId].second[_user];
	if (requestInfo.id == GET_GAME_RESULTS_RC)
	{
		PlayerResults playerResults;
		GetGameResultsResponse ggr = GetGameResultsResponse();
		try
		{
			getStatsRoom[_roomId].addUser(_user);
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		ggr.status = GET_GAME_RESULTS_STATUS;
		rr.newHandler = _rhf.createMenuRequestHandler(_user);
		try
		{
			if (getStatsRoom[_roomId].getAllUsers().size() != _rhf.getRoomManager().getRoom(_roomId).getAllUsers().size())
				throw std::runtime_error("not all the users in waiting room!");
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
		{
			if (this->roomsQuestions.find(_roomId) != this->roomsQuestions.end() && this->roomsQuestions.size() != 0)
			{
				this->roomsQuestions[_roomId].first.clear();
				getStatsRoom[_roomId].removeAllUsers();
			}
		}
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(ggr);
	}
	else if (requestInfo.id == SUBMIT_ANSWER_RC)
	{
		SubmitAnswerRequest sar = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
		SubmitAnswerResponse sarr = SubmitAnswerResponse();
		bool isCorrect = false;
		try
		{
			if (currentQuestion >= this->roomsQuestions[_roomId].first.size())
				throw std::runtime_error("question out of vectors bounds");
			if (sar.answer == this->roomsQuestions[_roomId].first[currentQuestion].getCA())
			{
				sarr.status = SUBMIT_ANSWER_CORRECT;
				isCorrect = true;
			}
			else sarr.status = SUBMIT_ANSWER_WRONG;
			this->_rhf.getGameManager().getGame(_user).setQuestionId(this->roomsQuestions[_roomId].first[currentQuestion].getId());
			this->_rhf.getGameManager().getGame(_user).setavrageTime((float)(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->avrageTime[_user]).count()) / FROM_MICRO_TO_SEC);
			QuestionStatistics* q = new QuestionStatistics(this->_rhf.getGameManager().getGame(_user), _user.getUserName(), isCorrect, sar.answer);
			this->_rhf.getStatisticsManager().addNewQuestionStatistics(*q);
			this->roomsQuestions[_roomId].second[_user]++;
			delete q;
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
			if (currentQuestion >= this->roomsQuestions[_roomId].first.size())
			{
				gqr.status = GET_QUESTION_ALL_QUESTIONS_ALREADY_ASKED;
				throw std::runtime_error("question out of vectors bounds");
			}
			gqr.question = this->roomsQuestions[_roomId].first[currentQuestion].getQ();
			gqr.answers.push_back(this->roomsQuestions[_roomId].first[currentQuestion].getCA());
			gqr.answers.push_back(this->roomsQuestions[_roomId].first[currentQuestion].getWA1());
			gqr.answers.push_back(this->roomsQuestions[_roomId].first[currentQuestion].getWA2());
			gqr.answers.push_back(this->roomsQuestions[_roomId].first[currentQuestion].getWA3());
		}
		catch (std::runtime_error& e)
		{
			gqr.status = GET_QUESTION_ERROR;
			std::cout << e.what() << std::endl;
		}
		rr.newHandler = _rhf.createGameRequestHandler(_user, _roomId);
		std::cout << "DEBUG: response code " << gqr.status << std::endl;
		this->avrageTime[_user] = std::chrono::high_resolution_clock::now();
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