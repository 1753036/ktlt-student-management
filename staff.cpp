#define _CRT_SECURE_NO_WARNINGS
#include "staff.h"

bool Staff::_running = true;
Setup *Staff::_setup = NULL;

void Staff::init(Setup *setup)
{
	_setup = setup;
}

void Staff::showMenu()
{
	Menu *acadMenu = new Menu("ACADEMIC STAFF");
	acadMenu->addItem("Import student from csv file", importStudent);
	acadMenu->addItem("Add a new student", addStudent);
	acadMenu->addItem("Edit an existing student", editStudent);
	acadMenu->addItem("Remove a student", removeStudent);
	acadMenu->addItem("Change class", changeClass);
	acadMenu->addItem("Add a new empty class", addEmptyClass);
	acadMenu->addItem("View list of classes", listClasses);
	acadMenu->addItem("View list of students in a class", listStudents);
	acadMenu->addItem("Import courses from a csv file", importCourses);
	acadMenu->addItem("Add a new course", addNewCourse);
	acadMenu->addItem("Edit an existing course", editCourse);
	acadMenu->addItem("Remove a course", removeCourse);
	acadMenu->addItem("View list of courses", listCourses);
	acadMenu->addItem("Import courses's schedules from a csv file", importSchedule);
	acadMenu->addItem("Add a course's schedule", addSchedule);
	acadMenu->addItem("Edit a course's schedule", removeSchedule);
	acadMenu->addItem("Remove a course's schedule", editSchedule);
	acadMenu->addItem("View list of schedules.", listSchedule);
	acadMenu->addItem("Search and view attendance list of a course", searchAttendanceCourse);
	acadMenu->addItem("Export attendance list to a csv file", exportAttendanceCourse);
	acadMenu->addItem("Search and view scoreboard of a course", searchScoreboard);
	acadMenu->addItem("Export a scoreboard to a csv file", exportScoreboard);
	acadMenu->addItem("Logout", logoutSession);
	
	while (_running)
		acadMenu->show();

	_setup = NULL;
	_running = true;
	delete acadMenu;
}

void Staff::importSchedule()
{
	char file[100];
	printf("Input file: ");
	std::cin >> file;
	std::cout << file << std::endl;
	FILE *F = fopen(file, "r");
	if (F == NULL) {
		printf("Not Found!");
		_getch();
		return;
	}
	_setup->schedule_count = getSchedule(F, _setup->schedules);
	fclose(F);	
}
void Staff::addSchedule()
{
	addCourse(_setup->schedules, _setup->schedule_count);
}
void Staff::removeSchedule()
{
	printSchedule(_setup->schedules, _setup->schedule_count);
}
void Staff::editSchedule()
{
	for (int i = 0; i < _setup->schedule_count; ++i)
		std::cout << i << " " << _setup->schedules[i].coursecode << std::endl;

	int n = 0;
	std::cout << "Choice: ";
	std::cin >> n;

	removeCourseSchl(_setup->schedules, _setup->schedule_count);
}
void Staff::listSchedule()
{
	for (int i = 0; i < _setup->schedule_count; ++i)
		std::cout << i << " " << _setup->schedules[i].coursecode 
		<< _setup->schedules[i].coursename 
		<< _setup->schedules[i].lecturername 
		<< _setup->schedules[i].semester << std::endl;

	_getch();
}
void Staff::searchAttendanceCourse(){}
void Staff::exportAttendanceCourse(){}
void Staff::searchScoreboard(){}
void Staff::exportScoreboard(){}

void Staff::logoutSession(){
	_running = false;
}