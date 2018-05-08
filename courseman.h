#pragma once

#include "csvloader.h"
#include "misc.h"

class CourseMan
{
public:
	CourseMan(std::string fileName);
	~CourseMan();

	void load(std::string fileName);
	void save(std::string fileName);
	void save();

	void add(Course* course);
	void addNew(std::string courseCode);

	void erase(Course* course);

	void importCsv(std::string fileName);

	Course* searchByCode(std::string code);

	std::list<Course *> getData();
private:
	std::string			_fileName;
	std::list<Course *> _listCourses;
};

