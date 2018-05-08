#define _CRT_SECURE_NO_WARNINGS
#include "lecturer.h"


Setup* Lecturer::_setup = NULL;
bool Lecturer::_running = true;


scoreboard Lecturer::S[1000];
int Lecturer::total;

void Lecturer::init(Setup* setup)
{
	_setup = setup;
}

void Lecturer::showMenu()
{
	Menu* menu = new Menu("LECTURER");
	menu->addItem("Import scoreboard of a course", importSB);
	menu->addItem("Edit grade of a student", editSB);
	menu->addItem("View a scoreboard", printSB);
	menu->addItem("Logout", logoutSession);

	while (_running)
		menu->show();

	_setup = NULL;
	_running = true;
	delete menu;

}


void Lecturer::importSB()
{
	printf("Input number of student: ");

	scanf("%i", &total);

	inputScoreboard(S, total);
	printScoreboard(S, total);
}

void Lecturer::editSB()
{
	editScoreboard(S, total);
}

void Lecturer::printSB()
{
	printScoreboard(S, total);
	_getch();
}

void Lecturer::logoutSession() {
	_running = false;
}