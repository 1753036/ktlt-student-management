#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Schoolyear
{
	int pre;
	int next;
};

struct date
{
	char *day;
	char *month;
	char *year;
};

struct Time
{
	char *hour;
	char *minute;
};

#define _CRT_SECURE_NO_WARNINGS
struct schedule
{
	int number;
	char *coursecode;
	Schoolyear year;
	int semester;
	char *coursename;
	char *lecturername;
	date start;
	date end;
	Time from;
	Time to;
	char *daysofWeek;
};

int getSchedule(FILE *f, schedule C[]);
void printSchedule(schedule C[], int totalofschedule);
void editSchedule(schedule C[], int n);
void addCourse(schedule C[], int &count);
void removeCourse(schedule C[], int &numberofschedule);
void printFile(schedule C[], int n);

