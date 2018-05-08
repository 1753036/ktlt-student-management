#pragma once

#include "setup.h"
#include "menu.h"
#include "CheckinMan.h"

class Student
{
public:
	static void init(Setup *setup);
	static void showMenu();
private:
	static bool	_running;
	static Setup *_setup;

	static void checkin();
	static void checkinStep1();

	static void viewResult();
	static void viewResultStep1();

	static void loadCkin();
	static void logoutSession();
};
