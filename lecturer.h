#pragma once
#include "menu.h"
#include "Scoreboard.h"
#include "setup.h"

class Lecturer
{
public:
	static void init(Setup *setup);
	static void showMenu();
private:
	static bool	_running;
	static Setup *_setup;

	static void importSB();
	static void editSB();
	static void printSB();

	static void logoutSession();

	static scoreboard S[1000];
	static int total;
};

