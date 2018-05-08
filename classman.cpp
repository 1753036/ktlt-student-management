#include "classman.h"

ClassMan::ClassMan(std::string fileName) { _fileName = fileName; }

ClassMan::~ClassMan()
{
	_fileName.clear();
	for (auto d : _classes)
		delete d;
}

void ClassMan::load()
{
	_stream.open(_fileName, std::ios::in);

	if (_stream.is_open() == false)
	{
		_stream.open(_fileName, std::ios::out);
		_stream.close();
		return;
	}

	std::string buffer;
	Class *cls = NULL;

	while(std::getline(_stream, buffer, DEFAULT_ENDLINE))
	{
		std::string className = Encoder::decode(buffer, DEFAULT_ENCODEPASS);
		if (className.length() < 10)
		{
			std::cout << className << std::endl;
			cls = addEmptyClass(className);
		} else {
			cls->load(buffer);
		}
	}

	_stream.close();
}

void ClassMan::save()
{
	_stream.open(_fileName, std::ios::out);

	for (auto d : _classes)
	{
		d->save(_stream);
	}

	_stream.close();
}

bool ClassMan::importCsv(std::string fileName)
{
	CsvLoader *csv = new CsvLoader(fileName);
	auto data = csv->getData();

	Class *curClass = NULL;
	User *curUser = NULL;

	for (unsigned i = 0; i < data.size(); ++i)
	{
		if (data[i][3] == "endc")
		{
			curClass = searchClass(data[i][0]);

			if (curClass == NULL)
				addEmptyClass(data[i][0]);

			continue;
		}

		curUser = curClass->addNew(data[i][0], data[i][1], UserStudent);

		if (curUser == NULL) continue;

		curUser->fullName = data[i][2];
		curUser->phoneNumber = data[i][3];

		curClass->addUser(curUser);
	}

	delete csv;
	return true;
}

Class *ClassMan::addEmptyClass(std::string className)
{
	if (className.length() == 0)
		return NULL;

	for (auto cls : _classes)
		if (cls->getClassName() == className)
			return NULL;

	Class *newClass = new Class(className);

	_classes.push_front(newClass);
	sort();
	return newClass;
}


Class *ClassMan::searchClass(std::string className)
{
	for (auto cls : _classes)
		if (cls->getClassName() == className)
			return cls;

	return NULL;
}

std::list<Class*> ClassMan::getClasses() { return _classes; }

unsigned ClassMan::countClass() { return _classes.size(); }

void ClassMan::sort()
{
	_classes.sort(compare);
}

bool ClassMan::compare(Class *a, Class *b)
{
	return a->getClassName() < b->getClassName();
}