#ifndef USERMAN_H
#define USERMAN_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

#include "encoder.h"
#include "basicstruct.h"
#include "md5hash.h"
#include "csvloader.h"

#define DEFAULT_ENCODEPASS "@123dsa"
#define DEFAULT_SEPARATOR '\034'
#define DEFAULT_ENDLINE '\033'

class Class
{
	public:
		Class(std::string className);
		~Class();
		void				load(std::string data);
		void				save(std::fstream &stream);

		void				addUser(User *user);

		User				*addNew();
		User				*addNew(std::string username);
		User				*addNew(std::string username, UserType type);
		User				*addNew(std::string username, std::string password);
		User				*addNew(std::string username, std::string password, UserType type);


		void				remove(User *user);
		void				erase(User *user);
		void				erase(std::string username);
		void				eraseAll();

		void				setPassword(User *user, std::string newPassword);

		bool				checkPassword(User *user, std::string password);

		User				*searchById(std::string id);
		User				*searchByName(std::string name);

		void				sortById();
		void				sortByName();

		std::string			getClassName();

		std::list<User *>	*getListStd();

		void				debugMsg();
	private:
		std::list<User *>	*_listUser;
		std::string			_className;

		static bool			comName(User *a, User *b);
		static bool			comId(User *a, User *b);
		static User			*readUser(std::string encStr, std::string className);
		static void			writeUser(std::fstream &stream, User *);
};

#endif // USERMAN_H
