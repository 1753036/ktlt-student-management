#pragma once

#include <string>
#include <fstream>

#include "encoder.h"
#include "class.h"

class ClassMan
{
	public:
		ClassMan(std::string fileName);
		~ClassMan();

		void			  load();
		void			  save();

		bool			  importCsv(std::string fileName);

		Class			  *addEmptyClass(std::string className);
		Class			  *searchClass(std::string className);

		unsigned		  countClass();

		void			  sort();

		std::list<Class*> getClasses();

	private:
		std::list<Class*> _classes;
		std::fstream	  _stream;
		std::string		  _fileName;

		static bool		  compare(Class *a, Class *b);
};
