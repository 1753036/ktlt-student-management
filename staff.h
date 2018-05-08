#include "misc.h"
#include "ledit.h"
#include "menu.h"
#include "table.h"
#include "setup.h"
#include "csvloader.h"
#include "ch_shedule.h"

class Staff
{
	public:
		static void init(Setup *setup);
		static void showMenu();
	private:
		static bool	_running;
		static Setup *_setup;

		static void importStudent();
		static void addStudent();
		static void addStudentNext();

		static void removeStudent();
		static void removeStudentStep1();
		static void removeStudentStep2();

		static void editStudent();
		static void editStudentStep1();
		static void editStudentStep2();

		static void changeClass();
		static void changeClassStep1();
		static void	changeClassStep2();
		static void changeClassStep3();

		static void addEmptyClass();
		static void listClasses();

		static void listStudents();
		static void listStudentsNext();

		static void importCourses();
		static void importCoursesStep1();

		static void addNewCourse();
		static void editCourse();
		static void removeCourse();
		static void listCourses();

		static void importSchedule();
		static void addSchedule();
		static void removeSchedule();
		static void editSchedule();
		static void listSchedule();
		static void searchAttendanceCourse();
		static void exportAttendanceCourse();
		static void searchScoreboard();
		static void exportScoreboard();

		static void logoutSession();

};