#include "SqliteDataBase.h"

bool SqliteDataBase::sendSQLMsg(const char* sql_command)
{
	const char* sqlStatementPerson = sql_command;
	char** errMessagePerson = nullptr;
	int res = sqlite3_exec(db, sqlStatementPerson, nullptr, nullptr, errMessagePerson);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return true;
}

int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	list<User>* users = (list<User>*)data;
	User* user = new User("", "", "");
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "USERNAME")
			user->setName(argv[i]);
		else if (string(azColName[i]) == "PASSWORD")
			user->setPass(argv[i]);
		else if (string(azColName[i]) == "EMAIL")
			user->setMail(argv[i]);
		else if (string(azColName[i]) == "ID")
			user->setId(std::stoi(argv[i]));
	}
	users->push_back(*user);
	return 0;
}

int callbackQuestion(void* data, int argc, char** argv, char** azColName)
{
	list<Question>* questions = (list<Question>*)data;
	Question* question = new Question("", "", "", "", "");
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "QUESTION")
			question->setQ(argv[i]);
		else if (string(azColName[i]) == "CORRECT_ANS")
			question->setCA(argv[i]);
		else if (string(azColName[i]) == "ANS2")
			question->setWA1(argv[i]);
		else if (string(azColName[i]) == "ANS3")
			question->setWA2(argv[i]);
		else if (string(azColName[i]) == "ANS4")
			question->setWA3(argv[i]);
		else if (string(azColName[i]) == "ID")
			question->setId(std::stoi(argv[i]));
	}
	questions->push_back(*question);
	return 0;
}

int callbackQuestionStatistics(void* data, int argc, char** argv, char** azColName)
{
	list<QuestionStatistics>* questionsStatistics = (list<QuestionStatistics>*)data;
	QuestionStatistics* questionStatistics = new QuestionStatistics("", 0.0, false, "");
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "USER_NAME")
			questionStatistics->setUserName(argv[i]);
		else if(string(azColName[i]) == "ANSWER")
			questionStatistics->setAnswer(argv[i]);
		else if (string(azColName[i]) == "IS_CORRECT")
			questionStatistics->setIsCorrect(bool(std::stoi(argv[i])));
		else if (string(azColName[i]) == "ANSWER_TIME")
			questionStatistics->setAnswerTime(time_t(argv[i]));
		else if (string(azColName[i]) == "QUESTION_ID")
			questionStatistics->setQuestionId(std::stoi(argv[i]));
		else if(string(azColName[i]) == "GAME_ID")
			questionStatistics->setGameId(std::stoi(argv[i]));
	}
	questionsStatistics->push_back(*questionStatistics);
	return 0;
}

list<QuestionStatistics> SqliteDataBase::getQuestionsStatistics()
{
	list<QuestionStatistics> questionsStatistics;
	const char* sqlStatement = "SELECT * FROM STATISTICS";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackQuestionStatistics, &questionsStatistics, &errMessage);
	if (res == SQLITE_OK)
		return questionsStatistics;
	std::cout << "Error getting db information - " << __func__ << std::endl;
	throw std::runtime_error("SQL Error getting users from DB!");
	return questionsStatistics;
}

list<Question> SqliteDataBase::getQuestions()
{
	list<Question> questions;
	const char* sqlStatement = "SELECT * FROM QUESTIONS";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackQuestion, &questions, &errMessage);
	if (res == SQLITE_OK)
		return questions;
	std::cout << "Error getting db information - " << __func__ << std::endl;
	throw std::runtime_error("SQL Error getting users from DB!");
	return questions;
}

list<User> SqliteDataBase::getUsers()
{
	list<User> users;
	const char* sqlStatement = "SELECT * FROM USERS";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackUser, &users, &errMessage);
	if (res == SQLITE_OK)
		return users;
	std::cout << "Error getting db information - " << __func__ << std::endl;
	throw std::runtime_error("SQL Error getting users from DB!");
	return users;
}

bool SqliteDataBase::isBigLetter(int ch)
{
	return ch >= 65 && ch <= 90;
}

bool SqliteDataBase::isNumber(int ch)
{
	return ch <= 57 && ch >= 48;
}

bool SqliteDataBase::isSmallLetter(int ch)
{
	return ch >= 97 && ch <= 122;
}

bool SqliteDataBase::open()
{
	bool users = true, questions = true, statistics = true;
	string dbFileName = "triviaDB.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (file_exist != 0)
	{
		users = sendSQLMsg("CREATE TABLE IF NOT EXISTS USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);");
		questions = sendSQLMsg("CREATE TABLE IF NOT EXISTS QUESTIONS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, CORRECT_ANS TEXT NOT NULL, ANS2 TEXT NOT NULL, ANS3 TEXT NOT NULL, ANS4 TEXT NOT NULL);");
		statistics = sendSQLMsg("CREATE TABLE IF NOT EXISTS STATISTICS(GAME_ID INTEGER NOT NULL, QUESTION_ID INT NOT NULL, USER_NAME TEXT NOT NULL, IS_CORRECT BOOLEAN NOT NULL, ANSWER TEXT NOT NULL,ANSWER_TIME REAL NOT NULL);");
		if(!users || !questions || !statistics)
		{
			std::cerr << "Error creating db!";
			return false;
		}

		addNewQuestion(Question("What is the name of your family doctor?", "Boris", "Arik", "Gavriel", "Ofek")); // 1
		addNewQuestion(Question("Which city is the capital of Israel?", "Jerusalem", "Tel Aviv", "Yavne", "Chernobyl"));// 1
		addNewQuestion(Question("Which country does not exist?", "Palestine", "Albania", "Kosovo", "Bosnia"));// 1
		addNewQuestion(Question("What is orange s color?", "Orange", "Red", "Black", "Purple"));
		addNewQuestion(Question("What is the best religion?", "Judaism", "Islam", "Christianity", "Being Palestinian"));// 1
		addNewQuestion(Question("First programming language is...", "Assembly", "Python", "C++", "C"));// 1
		addNewQuestion(Question("Which of the following is not a language?", "Palestinian", "Russian", "Hebrew", "English"));
		addNewQuestion(Question("Who is Jubzik?", "Liam", "Gavriels pet", "The Janitor", "Ofek"));
		addNewQuestion(Question("Who is Shmulik?", "Cyber Teacher", "Penguin", "Actor", "Diver"));
		addNewQuestion(Question("What is ofek s head shape?", "tangle", "rectangle", "dimoned", "unDeclared"));
	}
	else
	{
		res = sqlite3_open(dbFileName.c_str(), &db);
		if (res != SQLITE_OK)
		{
			std::cerr << "Failed to open DB!";
			return false;
		}
	}
	return true;
}

void SqliteDataBase::close()
{
	sqlite3_close(db);
	db = nullptr;
}

bool SqliteDataBase::isUserExist(const string name)
{
	list<User> users = getUsers();
	for (auto it = users.begin(); it != users.end(); ++it)
	{
		if (name == it->getName()) 
			return true;
	}
	return false;
}

bool SqliteDataBase::isUserExist(const string name, const string pass)
{
	list<User> users = getUsers();
	for (auto it = users.begin(); it != users.end(); ++it)
	{
		if (name == it->getName() && pass == it->getPass())
			return true;
	}
	return false;
}

bool SqliteDataBase::isPasswordMatch(const string password)
{
	bool atListOneBigLetter = false;
	bool thereSmallLetters = false;
	bool atListOneNumber = false;
	bool atListOneMark = false;
	for (auto it = password.begin(); it != password.end(); ++it)
	{
		if (isBigLetter(int(*it)))
			atListOneBigLetter = true;
		else if (isSmallLetter(int(*it)))
			thereSmallLetters = true;
		else if (isNumber(int(*it)))
			atListOneNumber = true;
		else atListOneMark = true;
	}
	return atListOneBigLetter && thereSmallLetters && atListOneNumber && atListOneMark;
}

void SqliteDataBase::addNewUser(User& user)
{
	std::string msg = "INSERT INTO USERS (USERNAME, PASSWORD,  EMAIL) VALUES ('" + user.getName() + "', '" + user.getPass() + "', '" + user.getMail() + "');";
	const char* sqlStatement = msg.c_str();
	if (sendSQLMsg(sqlStatement))
		std::cout << "user added successfully!\n";
	else std::cerr << "failed adding user!\n";
}

void SqliteDataBase::addNewQuestion(Question question)
{
	std::string msg = "INSERT INTO QUESTIONS (QUESTION, CORRECT_ANS,  ANS2, ANS3, ANS4) VALUES ('" + question.getQ() + "', '" + question.getCA() + "', '" + question.getWA1() + "', '" + question.getWA2() + "', '" + question.getWA3() + "');";
	const char* sqlStatement = msg.c_str();
	sendSQLMsg(sqlStatement);
}

void SqliteDataBase::addNewQuestionStatistics(QuestionStatistics stats)
{
	std::string msg = "INSERT INTO STATISTICS (GAME_ID, QUESTION_ID, USER_NAME, IS_CORRECT, ANSWER, ANSWER_TIME) VALUES ("
		+ std::to_string(stats.getGameId()) + ", "
		+ std::to_string(stats.getQuestionId()) + ", '"
		+ stats.getUserName() + "', "
		+ std::to_string(stats.getIsCorrect()) + ", '"
		+ stats.getAnswer() + "', "
		+ std::to_string(stats.getAnswerTime()) + ");";
	std::cout << msg;
	const char* sqlStatement = msg.c_str();
	sendSQLMsg(sqlStatement);
}

float SqliteDataBase::getPlayerAverageAnswerTime(string username)
{
	float AnswerTime = 0.0;
	int counter = 0;
	list<QuestionStatistics> questionsStatistics = getQuestionsStatistics();
	for (auto it = questionsStatistics.begin(); it != questionsStatistics.end(); ++it)
	{
		if (it->getUserName() == username)
		{
			counter++;
			AnswerTime += it->getAnswerTime();
		}
	}

	if (!counter)
	{
		std::cout << "OFEK IS 0" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "OFEK IS " << (AnswerTime / counter) << std::endl;

	}
	return AnswerTime / counter;
}

int SqliteDataBase::getNumOfCorrectAnswers(string username)
{
	int counter = 0;
	list<QuestionStatistics> questionsStatistics = getQuestionsStatistics();
	for (auto it = questionsStatistics.begin(); it != questionsStatistics.end(); ++it)
	{
		if (it->getIsCorrect() && it->getUserName() == username)
			counter++;

	}
	return counter;
}

int SqliteDataBase::getNumOfTotalAnswers(string username)
{
	int counter = 0;
	list<QuestionStatistics> questionsStatistics = getQuestionsStatistics();
	for (auto it = questionsStatistics.begin(); it != questionsStatistics.end(); ++it)
	{
		if (it->getUserName() == username)
			counter++;
	}
	return counter;
}

int SqliteDataBase::getNumOfPlayerGames(string username)
{
	int counter = 0;
	list<QuestionStatistics> questionsStatistics = getQuestionsStatistics();
	set<int> games;
	for (auto it = questionsStatistics.begin(); it != questionsStatistics.end(); ++it)
	{
		if (it->getUserName() == username && games.find(it->getGameId()) == games.end())
		{
			games.insert(it->getGameId());
			counter++;
		}
			
	}
	return counter;
}