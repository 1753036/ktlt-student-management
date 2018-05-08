#include "student.h"

Setup* Student::_setup = NULL;
bool Student::_running = true;

void Student::init(Setup* setup)
{
	_setup = setup;
}

void Student::showMenu()
{
	Menu* menu = new Menu("STUDENT");
	menu->addItem("Check-in", checkin);
	menu->addItem("View check-in result", NULL);
	menu->addItem("View score", NULL);
	menu->addItem("View schedules", NULL);
	menu->addItem("Logout", logoutSession);
	while (_running)
		menu->show();

	_setup = NULL;
	_running = true;
	delete menu;

}

void Student::checkin() {
	Menu* menu = new Menu("CHECKIN");
	for (auto d : _setup->getCourseMan()->getData())
		menu->addItem(d->courseCode, checkinStep1);
	menu->show();
	delete menu;

}

void Student::checkinStep1() {
	CheckinMan man(_setup, _setup->currentUser);
	man.checkNow(Menu::getTrigItem());
}

void Student::viewResult() {
	CheckinMan man(_setup, _setup->currentUser);
	man.showList();
}

void Student::logoutSession() {
	_running = false;
}

void Student::loadCkin() {

}