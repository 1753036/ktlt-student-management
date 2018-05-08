#include "staff.h"

void Staff::importStudent()
{
	LEdit *ledit = new LEdit("IMPORT CSV FILE");

	ledit->addItem("File Path");
	ledit->show();

	auto data = ledit->getVals();
	delete ledit;

	auto stdMan = _setup->getStudentMan();

	stdMan->importCsv(data[0]);
}
void Staff::addStudent()
{
	Menu *stdMenu = new Menu("ADD STUDENT TO A CLASS");
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->getClasses();

	for (auto cls : stdCls)
		stdMenu->addItem(cls->getClassName(), addStudentNext);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::addStudentNext()
{
	auto stdMenu = Menu::getTrigMenu();
	auto clsName = Menu::getTrigItem();

	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(clsName);

	LEdit ledit("ADD STUDENT");
	ledit.addItem("Username");
	ledit.show();

	auto data = ledit.getVals();

	stdCls->addNew(data[0]);
	_setup->save();

	stdMenu->show();


}

void Staff::removeStudent()
{
	Menu *stdMenu = new Menu("EDIT STUDENTS IN A CLASS");
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->getClasses();

	for (auto cls : stdCls)
		stdMenu->addItem(cls->getClassName(), removeStudentStep1);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::removeStudentStep1()
{
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(Menu::getTrigItem());
	Menu *stdMenu = new Menu(Menu::getTrigItem());

	for (auto std : *stdCls->getListStd())
		stdMenu->addItem(std->userName, removeStudentStep2);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::removeStudentStep2()
{
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(Menu::getTrigTit());
	auto stdMen = Menu::getTrigMenu();

	stdCls->erase(Menu::getTrigItem());
	stdMen->clear();

	for (auto std : *stdCls->getListStd())
		stdMen->addItem(std->userName, removeStudentStep2);
	stdMen->addItem("< Back >", NULL);

	stdMen->show();
}

void Staff::editStudent()
{
	Menu *stdMenu = new Menu("EDIT STUDENTS IN A CLASS");
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->getClasses();

	stdCls.sort();

	for (auto cls : stdCls)
		stdMenu->addItem(cls->getClassName(), editStudentStep1);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::editStudentStep1()
{
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(Menu::getTrigItem());
	Menu *stdMenu = new Menu(Menu::getTrigItem());

	stdCls->sortById();

	for (auto std : *stdCls->getListStd())
		stdMenu->addItem(std->userName, editStudentStep2);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::editStudentStep2()
{
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(Menu::getTrigTit());
	auto stdMen = Menu::getTrigMenu();
	
	User *std = stdCls->searchById(Menu::getTrigItem());

	LEdit *ledit = new LEdit("EDIT STUDENT");
	ledit->addItem("Fullname");
	ledit->addItem("Phone number");
	ledit->addItem("Password");
	ledit->show();

	auto data = ledit->getVals();


	std->fullName = data[0];
	std->phoneNumber = data[1];
	std->hashedPass = md5sum(data[2]);

	stdMen->show();
}

void Staff::changeClass()
{
	Menu *stdMenu = new Menu("CHANGE CLASS");
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->getClasses();

	for (auto cls : stdCls)
		stdMenu->addItem(cls->getClassName(), changeClassStep1);
	stdMenu->addItem("< Back >", NULL);

	stdMenu->show();
	delete stdMenu;
}

void Staff::changeClassStep1()
{
	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->searchClass(Menu::getTrigItem());

	LEdit *ledit = new LEdit("CHANGE CLASS");
	ledit->addItem("Username");
	ledit->addItem("Class");
	ledit->show();

	delete ledit;

	auto data = ledit->getVals();

	strToUpper(data[1]);

	auto user = stdCls->searchById(data[0]);
	auto clas = stdMan->searchClass(data[1]);

	if (user == NULL)
		return;

	if (clas == NULL)
		return;

	stdCls->remove(user);
	clas->addUser(user);
}

void Staff::addEmptyClass()
{
	LEdit *ledit = new LEdit("ADD AN EMPTY CLASS");
	ledit->addItem("Class");
	ledit->show();

	auto data = ledit->getVals();
	strToUpper(data[0]);

	delete ledit;

	auto stdMan = _setup->getStudentMan();
	auto stdCls = stdMan->addEmptyClass(data[0]);

	stdMan->sort();
	_setup->save();
}

void Staff::importCourses()
{
	LEdit *ledit = new LEdit("IMPORT COURSES FROM CSV");
	ledit->addItem("Csv File");
	ledit->show();

	auto data = ledit->getVals();
	delete ledit;

	_setup->getCourseMan()->importCsv(data[0]);
}

void Staff::addNewCourse() 
{
	LEdit *ledit = new LEdit("ADD NEW COURSE");

	ledit->addItem("Course Code");
	ledit->addItem("Course Name");
	ledit->addItem("Lecturer Name");
	ledit->addItem("Year");
	ledit->addItem("Semester");
	ledit->addItem("Start Date");
	ledit->addItem("End Date");
	ledit->addItem("Start Time");
	ledit->addItem("End Time");
	ledit->addItem("Day of week(0~6)");
	ledit->show();
	auto data = ledit->getVals();
	delete ledit;

	Course* course = new Course;

	course->courseCode = data[0];
	course->courseName = data[1];
	course->lecturerName = data[2];
	course->year = data[3];
	course->semester = std::stoi(data[4]);
	course->startDate = data[5];
	course->endDate = data[6];
	course->startTime = data[7];
	course->endTime = data[8];
	course->dayOfWeek = std::stoi(data[9]);

	_setup->getCourseMan()->add(course);
}
void Staff::editCourse() 
{
	auto data = _setup->getCourseMan()->getData();
	int i = 0;
	int choice = -1;
	Course* course = NULL;
	for (auto d : data)
	{
		std::cout << "[*] " << i++ << " - " << d->courseCode << ":" << d->courseName << ":" << intToDay(d->dayOfWeek);
		std::cout << ":" << d->semester;
		std::cout << ":" << d->year;
		std::cout << ":" << d->startDate << " -> " << d->endDate;
		std::cout << ":" << d->startTime << " -> " << d->endTime << std::endl;
	}
	std::cout << "Your choice: ";
	std::cin >> choice;
	for (auto d : data)
	{
		if (choice == 0)
			course = d;
		--choice;
	}

	LEdit *ledit = new LEdit("ADD NEW COURSE");

	ledit->addItem("Course Code");
	ledit->addItem("Course Name");
	ledit->addItem("Lecturer Name");
	ledit->addItem("Year");
	ledit->addItem("Semester");
	ledit->addItem("Start Date");
	ledit->addItem("End Date");
	ledit->addItem("Start Time");
	ledit->addItem("End Time");
	ledit->addItem("Day of week(0~6)");
	ledit->show();
	auto ldata = ledit->getVals();
	delete ledit;

	course->courseCode = ldata[0];
	course->courseName = ldata[1];
	course->lecturerName = ldata[2];
	course->year = ldata[3];
	course->semester = std::stoi(ldata[4]);
	course->startDate = ldata[5];
	course->endDate = ldata[6];
	course->startTime = ldata[7];
	course->endTime = ldata[8];
	course->dayOfWeek = std::stoi(ldata[9]);
}
void Staff::removeCourse() 
{
	auto data = _setup->getCourseMan()->getData();
	int i = 0;
	int choice = -1;
	for (auto d : data)
	{
		std::cout << "[*] " << i++ << " - " << d->courseCode << ":" << d->courseName << ":" << intToDay(d->dayOfWeek);
		std::cout << ":" << d->semester;
		std::cout << ":" << d->year;
		std::cout << ":" << d->startDate << " -> " << d->endDate;
		std::cout << ":" << d->startTime << " -> " << d->endTime << std::endl;
	}
	std::cout << "Your choice: ";
	std::cin >> choice;
	for (auto d : data)
	{
		if (choice == 0)
			_setup->getCourseMan()->erase(d);
		--choice;
	}
}
void Staff::listCourses()
{
	auto data = _setup->getCourseMan()->getData();
	for (auto d : data)
	{
		std::cout << d->courseCode << ":" << d->courseName << ":" << intToDay(d->dayOfWeek) << std::endl;
		std::cout << "    [+] " << d->semester << std::endl;
		std::cout << "    [+] " << d->year << std::endl;
		std::cout << "    [+] " << d->startDate << " -> " << d->endDate << std::endl;
		std::cout << "    [+] " << d->startTime << " -> " << d->endTime << std::endl;
		std::cout << std::endl;
	}
	_getch();
}