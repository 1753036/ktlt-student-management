#include "class.h"

/*
 * Being normal is boring
 */

Class::Class(std::string className)
	: _listUser(new std::list<User *>)
	, _className(className)
{
}

Class::~Class()
{
	eraseAll();
}

/*
 * Load and save Class type file, just a trick ^^
 * it is my custom type, it is not secure
 */

void Class::load(std::string data)
{
	addUser(readUser(data, _className));
	sortById();
}

void Class::save(std::fstream &stream)
{
	std::string buffer;
	stream << Encoder::encode(_className, DEFAULT_ENCODEPASS) << DEFAULT_ENDLINE;
	for (User *user : *_listUser)
		writeUser(stream, user);
}

/*
 * Static members for reading and writing
 * readUser means parse a string and set to a new user
 * writeUser means write an existing user to a output stream
 */

User *Class::readUser(std::string encStr, std::string className)
{
	User *user = new User;

	std::stringstream stream(encStr);
	std::string buffer;

	std::getline(stream, buffer, DEFAULT_SEPARATOR);
	user->userName = Encoder::decode(buffer, DEFAULT_ENCODEPASS);

	std::getline(stream, buffer, DEFAULT_SEPARATOR);
	user->fullName = Encoder::decode(buffer, DEFAULT_ENCODEPASS);

	std::getline(stream, buffer, DEFAULT_SEPARATOR);
	user->email = Encoder::decode(buffer, DEFAULT_ENCODEPASS);

	std::getline(stream, buffer, DEFAULT_SEPARATOR);
	user->phoneNumber = Encoder::decode(buffer, DEFAULT_ENCODEPASS);

	std::getline(stream, buffer, DEFAULT_SEPARATOR);
	switch (std::stoi(Encoder::decode(buffer, DEFAULT_ENCODEPASS)))
	{
		case 0: user->userType = UserStudent; break;
		case 1: user->userType = UserAcademicStaff; break;
		case 2: user->userType = UserLecturer; break;
	}

	std::getline(stream, buffer, DEFAULT_SEPARATOR);
	user->hashedPass = Encoder::decode(buffer, DEFAULT_ENCODEPASS);

	user->className = className;

	return user;
}

void Class::writeUser(std::fstream &stream, User *user)
{
	if (user == NULL)
		return;
	stream << Encoder::encode(user->userName, DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
	stream << Encoder::encode(user->fullName, DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
	stream << Encoder::encode(user->email, DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
	stream << Encoder::encode(user->phoneNumber, DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
	switch (user->userType)
	{
		case UserStudent:
			stream << Encoder::encode("0", DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
			break;
		case UserAcademicStaff:
			stream << Encoder::encode("1", DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
			break;
		case UserLecturer:
			stream << Encoder::encode("2", DEFAULT_ENCODEPASS) << DEFAULT_SEPARATOR;
			break;
	}

	stream << Encoder::encode(user->hashedPass, DEFAULT_ENCODEPASS) << DEFAULT_ENDLINE;
}

/*
 * Add or remove/erase an existing user
 * Add a new user and return it
 */

void Class::remove(User *user)
{
	if (user == NULL)
		return;

	_listUser->remove(user);
}

void Class::erase(User *user)
{
	if (user == NULL)
		return;

	remove(user);
	delete user;
}

void Class::erase(std::string username)
{
	erase(searchById(username));
}

void Class::eraseAll()
{
	for (User *user : *_listUser) delete user;
	_listUser->clear();
}

void Class::addUser(User *exUser)
{
	for (User *user : *_listUser)
	{
		if (exUser == user)
		{
			delete exUser;
			return;
		}
	}

	_listUser->push_front(exUser);
}

User *Class::addNew()
{
	User *newUser = new User;
	newUser->className = _className;
	newUser->fullName = "Unknown";
	newUser->userName = "Unknown";
	newUser->email = "Unknown";
	newUser->phoneNumber = "0";
	newUser->userType = UserStudent;
	newUser->hashedPass = md5sum("1");
	_listUser->push_front(newUser);
	return newUser;
}

User *Class::addNew(std::string username)
{
	if (searchById(username) != NULL || username.length() == 0)
		return NULL;
//	std::cout << username << std::endl;
	User *newUser = addNew();
	newUser->userName = username;
	newUser->hashedPass = md5sum(username);
	return newUser;
}

User *Class::addNew(std::string username, UserType type)
{
	if (searchById(username) != NULL)
		return NULL;

	User *newUser = addNew(username);
	newUser->userType = type;
	return newUser;
}

User *Class::addNew(
		std::string username,
		std::string password)
{
	if (searchById(username) != NULL)
		return NULL;

	User *newUser = addNew();
	newUser->userName = username;
	newUser->hashedPass = md5sum(password);
	return newUser;
}


User *Class::addNew(
		std::string username,
		std::string password,
		UserType type)
{
	if (searchById(username) != NULL)
		return NULL;

	User *newUser = addNew(username, password);
	newUser->userType = type;
	return newUser;
}




void Class::setPassword(User *user, std::string newPassword)
{
	user->hashedPass = md5sum(newPassword);
}

bool Class::checkPassword(User *user, std::string password)
{
	if (user->hashedPass == md5sum(password))
		return true;
	return false;
}

/*
 * Search an existing user from _listUser
 * search by id(username) and search by name(fullname)
 */

User *Class::searchById(std::string id)
{
	if (_listUser == NULL)
		return NULL;

	for (User *user : *_listUser)
		if (user->userName == id)
			return user;
	return NULL;
}

User *Class::searchByName(std::string name)
{
	for (User *user : *_listUser)
		if (user->fullName == name)
			return user;
	return NULL;
}

/*
 * Sort list of users
 * We have two sorting methods
 * Sort by id (username)
 * Sort by name (fullname)
 */

void Class::sortById()
{
	_listUser->sort(comId);
}

void Class::sortByName()
{
	_listUser->sort(comName);
}

bool Class::comName(User *a, User *b)
{
	return a->fullName < b->fullName;
}

bool Class::comId(User *a, User *b)
{
	return a->userName < b->userName;
}

std::string Class::getClassName()
{
	return _className;
}

std::list<User *> *Class::getListStd()
{
	return _listUser;
}

/*
 * Debug Message, it print down all users in _listUser,
 * Including info of an existing user
 * if the user is'not existing, it will print ERROR message
 */

void Class::debugMsg()
{
	for (User *user : *_listUser)
	{
		if (user == NULL)
		{
			std::cout << " [*] ERROR : The user " << user << " does not exist" << std::endl;
			continue;
		}

		std::cout << " [+] " << user->userName << " : " << user->hashedPass << " | " << user->fullName << " : " << user->email << " : " << user->phoneNumber << std::endl;
	}
}
