#include "staff.h"

void Staff::listClasses()
{
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->getClasses();

	for (auto cls : stdCls)
		std::cout << cls->getClassName() << std::endl;

	_getch();
}
void Staff::listStudents()
{
	Menu *stdMenu = new Menu("VIEW STUDENTS IN A CLASS");
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->getClasses();

	for (auto cls : stdCls)
		stdMenu->addItem(cls->getClassName(), listStudentsNext);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::listStudentsNext()
{
	auto stdMenu = Menu::getTrigMenu();
	auto clsName = Menu::getTrigItem();

	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(clsName);

	stdCls->debugMsg();
	_getch();
	stdMenu->show();
}