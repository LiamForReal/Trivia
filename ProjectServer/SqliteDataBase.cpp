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
	std::list<User>* users = (std::list<User>*)data;
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

std::list<User> SqliteDataBase::getUsers()
{
	std::list<User> users;
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
	string dbFileName = "triviaDB.sqlite";
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (file_exist != 0)
	{
		if (!sendSQLMsg("CREATE TABLE IF NOT EXISTS USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);"))
		{
			std::cerr << "Error creating db!";
			return false;
		}
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
	std::list<User> users = getUsers();
	for (auto it = users.begin(); it != users.end(); ++it)
	{
		if (name == it->getName()) 
			return true;
	}
	return false;
}

bool SqliteDataBase::isUserExist(const string name, const string pass)
{
	std::list<User> users = getUsers();
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
	std::list<User> listUsers = getUsers();
	string password = "";

	do 
	{
		std::cout << "your password dont strong enoght\nEnter your password: ";
		std::cin >> password;
		user.setPass(password);
	} while ((!isPasswordMatch(user.getPass())));

	std::string msg = "INSERT INTO USERS (USERNAME, PASSWORD,  EMAIL) VALUES ('" + user.getName() + "', '" + user.getPass() + "', '" + user.getMail() + "');";
	const char* sqlStatement = msg.c_str();
	if (sendSQLMsg(sqlStatement))
		std::cout << "user added successfully!\n";
	else std::cerr << "failed adding user!\n";
}