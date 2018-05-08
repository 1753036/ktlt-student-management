#define _CRT_SECURE_NO_WARNINGS
#pragma once

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

struct Date
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

struct Schedule
{
	int number;
	char *coursecode;
	Schoolyear year;
	int semester;
	char *coursename;
	char *lecturername;
	Date start;
	Date end;
	Time from;
	Time to;
	char *daysofWeek;
};

int getSchedule(FILE *f, Schedule C[]);
void printSchedule(Schedule C[], int totalofSchedule);
void editSchedule(Schedule C[], int n);
void addCourse(Schedule C[], int &count);
void removeCourseSchl(Schedule C[], int &numberofSchedule);
void printFile(Schedule C[], int n);

