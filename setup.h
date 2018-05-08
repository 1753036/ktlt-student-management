#ifndef SETUP_H
#define SETUP_H

#include "classman.h"
#include "class.h"
#include "courseman.h"
#include "ch_shedule.h"

class Setup
{
	public:
		Setup();
		~Setup();

		ClassMan *getStaffMan();
		ClassMan *getStudentMan();
		ClassMan *getLecturerMan();
		CourseMan *getCourseMan();

		void	 save();
		void	 load();

		std::string currentUser;
		Schedule schedules[100];
		int schedule_count;
	private:
		ClassMan  *_staff = NULL;
		ClassMan  *_student = NULL;
		ClassMan  *_lecturer = NULL;
		CourseMan *_course = NULL;
};

#endif // SETUP_H
