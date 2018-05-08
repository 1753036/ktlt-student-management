#define _CRT_SECURE_NO_WARNINGS

#include "courseman.h"



CourseMan::CourseMan(std::string fileName)
{
	_fileName = fileName;
	load(fileName);
}


CourseMan::~CourseMan()
{
	for (auto d : _listCourses)
		delete d;
	_listCourses.clear();
}

void CourseMan::importCsv(std::string fileName)
{
	CsvLoader* csv = new CsvLoader(fileName);
	auto data = csv->getData();
	if (data.size() == 0)
		return;

	Course* course = NULL;

	for (unsigned i = 0; i < data.size(); ++i)
	{
		course = new Course;

		course->courseCode		= data[i][0];
		course->courseName		= data[i][1];
		course->lecturerName	= data[i][2];
		course->year			= data[i][3];
		course->semester		= std::stoi(data[i][4]);
		course->startDate		= data[i][5];
		course->endDate			= data[i][6];
		course->startTime		= data[i][7];
		course->endTime			= data[i][8];
		course->dayOfWeek		= std::stoi(data[i][9]);

		add(course);
	}

	delete csv;
}

void CourseMan::add(Course* course)
{
	if (course == NULL)
		return;

	for (auto d : _listCourses)
	{
		if (course->courseCode == d->courseCode &&
			course->startTime == d->startTime &&
			course->startDate == d->startDate &&
			course->dayOfWeek == d->dayOfWeek)
		{
			delete course;
			return;
		}
		if (course == d)
			return;
	}

	_listCourses.push_back(course);
}

void CourseMan::erase(Course *course)
{
	_listCourses.remove(course);
	delete course;
}

void CourseMan::addNew(std::string courseCode)
{
	Course *newCou = new Course;

	newCou->courseCode = courseCode;
	newCou->courseName = "Unknown";
	newCou->lecturerName = "Unknown";
	newCou->year = "Unknown";
	newCou->semester = 0;
	newCou->startDate = "Unknown";
	newCou->endDate = "Unknown";
	newCou->startTime = "Unknown";
	newCou->endTime = "Unknown";
	newCou->dayOfWeek = 0;

	_listCourses.push_back(newCou);
}

Course* CourseMan::searchByCode(std::string code)
{
	for (auto d : _listCourses)
		if (d->courseCode == code)
			return d;
	return NULL;
}

void CourseMan::load(std::string fileName)
{
	importCsv(fileName);
}

void CourseMan::save(std::string fileName)
{
	std::ofstream stream(fileName);
	for (auto d : _listCourses)
	{
		stream << d->courseCode << ",";
		stream << d->courseName << ",";
		stream << d->lecturerName << ",";
		stream << d->year << ",";
		stream << d->semester << ",";
		stream << d->startDate << ",";
		stream << d->endDate << ",";
		stream << d->startTime << ",";
		stream << d->endTime << ",";
		stream << d->dayOfWeek << std::endl;
	}
	stream.close();
}

void CourseMan::save()
{
	save(_fileName);
}

std::list<Course *> CourseMan::getData()
{
	return _listCourses;
}