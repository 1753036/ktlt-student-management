#define _CRT_SECURE_NO_WARNINGS
#include "CheckinMan.h"



CheckinMan::CheckinMan(Setup* setup, std::string id)
{
	_id = id;
	_setup = setup;

	if (std::ifstream(id).is_open() == false)
		return;

	CsvLoader* csv = new CsvLoader(id);
	auto data = csv->getData();
	if (data.size() == 0)
		return;

	CheckinStr* ckin = new CheckinStr;

	for (unsigned i = 0; i < data.size(); ++i)
	{
		ckin->courseCode = data[i][0];
		ckin->time = data[i][1];

		_listCkin.push_back(ckin);
	}

	delete csv;
}


CheckinMan::~CheckinMan()
{
	std::ofstream stream(_id);
	for (auto d : _listCkin)
	{
		stream << d->courseCode << ',';
		stream << d->time << std::endl;
	}
	stream.close();

	for (auto d : _listCkin)
		delete d;
	_listCkin.clear();
}


void CheckinMan::checkNow(std::string code)
{
	//@TODO
	Course* course = _setup->getCourseMan()->searchByCode(code);
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	std::string timeNow = std::to_string(now->tm_hour)
		+ ":" + std::to_string(now->tm_min);

	std::cout << code << " | ";
	std::cout << timeNow << std::endl;
	_getch();
}

void CheckinMan::showList()
{
	for (auto d : _listCkin)
		std::cout << d->courseCode << " " << d->time << std::endl;
	_getch();
}