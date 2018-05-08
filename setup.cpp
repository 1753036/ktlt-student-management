#include "setup.h"

Setup::Setup()
{ 
	_staff	  = new ClassMan("data/staff");
	_lecturer = new ClassMan("data/lecturer");
	_student  = new ClassMan("data/student");
	_course   = new CourseMan("data/course");
	_staff->load();
	_lecturer->load();
	_student->load();

}

Setup::~Setup()
{ 
	save(); 
	delete _staff;
	delete _lecturer;
	delete _student;
	delete _course;
}

ClassMan *Setup::getStaffMan()
{
	return _staff;
}
ClassMan *Setup::getStudentMan()
{
	return _student;
}
ClassMan *Setup::getLecturerMan()
{
	return _lecturer;
}

CourseMan *Setup::getCourseMan()
{
	return _course;
}

void Setup::save()
{
	_staff->save();
	_lecturer->save();
	_student->save();
	_course->save();
}