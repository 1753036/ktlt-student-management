#pragma once

#include "misc.h"
#include "setup.h"

struct CheckinStr{
	std::string courseCode;
	std::string time;
};

class CheckinMan
{
public:
	CheckinMan(Setup* setup, std::string id);
	~CheckinMan();

	void checkNow(std::string code);
	void showList();
private:
	std::list<CheckinStr*>	_listCkin;
	std::string				_id;
	Setup*					_setup;
};

