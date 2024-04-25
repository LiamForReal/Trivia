#include "SqliteDataBase.h"

bool SqliteDataBase::sendSQLMsg(const char* sql_command)
{
	const char* sqlStatementPerson = sql_command;
	char** errMessagePerson = nullptr;
	int res = sqlite3_exec(db, sqlStatementPerson, nullptr, nullptr, errMessagePerson);
	if (res != SQLITE_OK)
	{
		std::cout << "false";
		return false;
	}
	std::cout << "true";
	return true;
}

int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	std::vector<User>* users = (std::vector<User>*)data;
	User* user = new User("", "", "");
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "USERNAME")
			user->setName(argv[i]);
		else if (string(azColName[i]) == "PASSWORD")
			user->setPass(argv[i]);
		else if (string(azColName[i]) == "EMAIL")
			user->setMail(argv[i]);
	}
	users->push_back(*user);
	return 0;
}

int callbackQuestion(void* data, int argc, char** argv, char** azColName)
{
	std::vector<Question>* questions = (std::vector<Question>*)data;
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
	}
	questions->push_back(*question);
	return 0;
}

std::vector<Question> SqliteDataBase::getQuestions()
{
	std::vector<Question> questions;
	const char* sqlStatement = "SELECT * FROM QUESTIONS";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackQuestion, &questions, &errMessage);
	if (res == SQLITE_OK)
		return questions;
	std::cout << "Error getting db information - " << __func__ << std::endl;
	throw std::runtime_error("SQL Error getting users from DB!");
	return questions;
}

std::vector<User> SqliteDataBase::getUsers()
{
	std::vector<User> users;
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
		questions = sendSQLMsg("CREATE TABLE IF NOT EXISTS QUESTIONS(QUESTION_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, CORRECT_ANS TEXT NOT NULL, ANS2 TEXT NOT NULL, ANS3 TEXT NOT NULL, ANS4 TEXT NOT NULL);");
		//statistics = sendSQLMsg("CREATE TABLE IF NOT EXISTS STATISTICS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USER_NAME TEXT NOT NULL, NUM_OF_GAMES INT NOT NULL, NUM_OF_RIGHT_ANS INT NOT NULL, NUM_OF_WRONG_ANS INT NOT NULL, AVRAGE_TIME_FOR_ANS REAL NOT NULL);");
		if(!users || !questions || !statistics)
		{
			std::cerr << "Error creating db!";
			return false;
		}

		addNewQuestion(Question("What the name of your family doctor?", "boris", "aric", "gavriel", "ofek"));
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
	std::vector<User> users = getUsers();
	for (auto it = users.begin(); it != users.end(); ++it)
	{
		if (name == it->getName()) 
			return true;
	}
	return false;
}

bool SqliteDataBase::isUserExist(const string name, const string pass)
{
	std::vector<User> users = getUsers();
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