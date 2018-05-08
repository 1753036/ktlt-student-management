#include "menu.h"
#include "setup.h"
#include "student.h"
#include "lecturer.h"
#include "staff.h"
Setup *g_setup = new Setup();
Menu *g_menu = new Menu("STUDENT MANAGEMENT SYSTEM");
bool g_running = true;

void login();
void chpwd();
void about();
void exitP();

bool checkStaff(std::string username, std::string password);
bool checkStd(std::string username, std::string password);
bool checkLec(std::string username, std::string password);

int main()
{


	g_menu->addItem("Login", login);
	g_menu->addItem("Change Password", chpwd);
	g_menu->addItem("About", about);
	g_menu->addItem("Exit", exitP);


	while (g_running)
		g_menu->show();

	delete g_setup;
	delete g_menu;
	return 0;
}

void login()
{
	std::string username = getPassword("Username: ", 1, false);
	std::string password = getPassword("Password: ", 2, true);

	g_setup->currentUser = username;

	if (checkStaff(username, password))
	{
		Staff::init(g_setup);
		Staff::showMenu();
		return;
	}

	if (checkLec(username, password))
	{
		Lecturer::init(g_setup);
		Lecturer::showMenu();
		return;
	}

	if (checkStd(username, password))
	{
		Student::init(g_setup);
		Student::showMenu();
		return;
	}
}

void chpwd()
{
	g_setup->save();
}

void about()
{
	std::cout << "MUAAHAHAHA" << std::endl;
	_getch();
}
void exitP()
{
	g_running = false;
}

bool checkStaff(std::string username, std::string password)
{
	auto staffMan = g_setup->getStaffMan();
	auto staffCls = staffMan->searchClass("STAFF");
	auto staffUsr = staffCls->searchById(username);

	if (staffUsr == NULL)
		return false;

	if (staffCls->checkPassword(staffUsr, password) == false)
		return false;

	return true;
}

bool checkLec(std::string username, std::string password)
{
	auto staffMan = g_setup->getLecturerMan();
	auto staffCls = staffMan->searchClass("LECTURER");
	auto staffUsr = staffCls->searchById(username);

	if (staffUsr == NULL)
		return false;

	if (staffCls->checkPassword(staffUsr, password) == false)
		return false;

	return true;
}

bool checkStd(std::string username, std::string password)
{
	auto stdMan = g_setup->getStudentMan();
	auto stdCls = stdMan->getClasses();
		
	for (auto d : stdCls)
	{
		auto student = d->searchById(username);
		if (student)
		{
			if (d->checkPassword(student, password))
			{
				return true;
			}
		}
	}
	return false;
}