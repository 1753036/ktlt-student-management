#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include "schedule.h"


using namespace std;
int getSchedule(FILE *f, schedule C[])
{
	char buf[100];
	char *token;
	int n = 0;
	
	while (fgets(buf, 100, f))
	{
		token = strtok(buf, ",");
		//Chép mã môn
		C[n].coursecode = _strdup(token);
		//Chép tên môn
		token = strtok(NULL, ",");
		C[n].coursename= _strdup(token);
		//Chép tên GV
		token = strtok(NULL, ",");
		C[n].lecturername = _strdup(token);
		//Chép năm học
		
		token = strtok(NULL, ",");
		char *a= _strdup(token);
		C[n].year.next = atoi(a);
		//Chép học kì
		
		token = strtok(NULL, ",");
		char *sem = _strdup(token);
		C[n].semester = atoi(sem);
		//Chép ngày bắt đầu
		token = strtok(NULL, "/");
		C[n].start.day = _strdup(token);
		token = strtok(NULL, "/");
		C[n].start.month = _strdup(token);
		token = strtok(NULL, ",");
		C[n].start.year = _strdup(token);
		//Chép ngày kết thúc
		
		token = strtok(NULL, "/");
		C[n].end.day = _strdup(token);
		token = strtok(NULL, "/");
		C[n].end.month = _strdup(token);
		token = strtok(NULL, ",");
		C[n].end.year = _strdup(token);
		// Chép giờ bắt đầu
	
		token = strtok(NULL, ":");
		C[n].from.hour = _strdup(token);
		token = strtok(NULL, ",");
		C[n].from.minute = _strdup(token);
		//Chép giờ kết thúc
		
		token = strtok(NULL, ":");
		C[n].to.hour = _strdup(token);
	
		token = strtok(NULL, ",");
		C[n].to.minute = _strdup(token);
		//Chép số ngày học trong tuần
		
		token = strtok(NULL, ",");
		C[n].daysofWeek = _strdup(token);
		n++;
	}
	return n;
}

void printSchedule(schedule C[], int totalofcourse)
{
	cin.ignore();
	if (C == NULL)
	{
		printf("Empty schedule!");
	}
	else
	{
		for (int i = 0; i < totalofcourse; i++)
		{
			printf("%s,%s,%s,%i,%i,%s/%s/%s,%s/%s/%s,%s:%s,%s:%s,%s\n", C[i].coursecode, C[i].coursename, C[i].lecturername, C[i].year.next,
				C[i].semester, C[i].start.day, C[i].start.month, C[i].start.year,
				C[i].end.day, C[i].end.month, C[i].end.year,
				C[i].from.hour, C[i].from.minute,
				C[i].to.hour, C[i].to.minute,
				C[i].daysofWeek);
			
		}
	}
}

void editSchedule(schedule C[], int n)
{
	char  coursecode[100];
	cin.ignore();
	printf("Input course code you need to change:");
	gets_s(coursecode);
	int flag = 0;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(coursecode,C[i].coursecode)==0)
		{
			flag = 1;
			break;
		}
		count++;
	}
	if (flag == 0)
	{
		printf("schedule not found!");
		return;
	}
	else
	{
		printf("Input course name:");
		char name[100];
		gets_s(name);
		C[count].coursename = _strdup(name);
		puts(C[count].coursename);
		printf("Input lecturer name: ");
		char lecturer[1000];
		gets_s(lecturer);
		C[count].lecturername = _strdup(lecturer);
		puts(C[count].lecturername);
		printf("Input schoolyear: ");
		char year[5];
		gets_s(year);
		C[count].year.next = atoi(year);
		printf("%i\n", C[count].year.next);
		printf("Input semester: ");
		char sem[2];
		gets_s(sem);
		C[count].semester = atoi(sem);
		printf("%i\n", C[count].semester);
		printf("Input start day: ");
		char day1[3];
		gets_s(day1);
		char month1[3];
		gets_s(month1);
		char year1[5];
		gets_s(year1);
		C[count].start.day = _strdup(day1);
		C[count].start.month = _strdup(month1);
		C[count].start.year = _strdup(year1);
		printf("\n%s-%s-%s\n", C[count].start.day, C[count].start.month, C[count].start.year);
		printf("Input end day: ");
		char day2[3];
		gets_s(day2);
		char month2[3];
		gets_s(month2);
		char year2[5];
		gets_s(year2);
		C[count].end.day = _strdup(day2);
		C[count].end.month = _strdup(month2);
		C[count].end.year = _strdup(year2);
		printf("\n%s-%s-%s\n", C[count].end.day, C[count].end.month, C[count].end.year);
		printf("Input start hour: ");
		char hour1[3];
		char minute1[3];
		gets_s(hour1);
		gets_s(minute1);
		C[count].from.hour = _strdup(hour1);
		C[count].from.minute = _strdup(minute1);
		printf("%s:%s\n", C[count].from.hour, C[count].from.minute);
		printf("Input end hour: ");
		char hour2[3];
		char minute2[3];
		gets_s(hour2);
		gets_s(minute2);
		C[count].to.hour = _strdup(hour2);
		C[count].to.minute = _strdup(minute2);
		printf("%s:%s\n", C[count].to.hour, C[count].to.minute);
		printf("Input number of days in a week has this course: ");
		char dayc[2];
		gets_s(dayc);
		C[count].daysofWeek = _strdup(dayc);
		printf("%s", C[count].daysofWeek);
	}
}

void addCourse(schedule C[], int &count) //count: số khóa học (schedule)
{
	count = count + 1;
	printf("Input schedule code:");
	char code[7];
	gets_s(code);
	C[count].coursecode = _strdup(code);
	printf("Input schedule name:");
	char name[100];
	gets_s(name);
	C[count].coursename = _strdup(name);
	puts(C[count].coursename);
	printf("Input lecturer name: ");
	char lecturer[1000];
	gets_s(lecturer);
	C[count].lecturername = _strdup(lecturer);
	puts(C[count].lecturername);
	printf("Input schoolyear: ");
	char year[5];
	gets_s(year);
	C[count].year.next = atoi(year);
	printf("%i\n", C[count].year.next);
	printf("Input semester: ");
	char sem[2];
	gets_s(sem);
	C[count].semester = atoi(sem);
	printf("%i\n", C[count].semester);
	printf("Input start day: ");
	char day1[3];
	gets_s(day1);
	char month1[3];
	gets_s(month1);
	char year1[5];
	gets_s(year1);
	C[count].start.day = _strdup(day1);
	C[count].start.month = _strdup(month1);
	C[count].start.year = _strdup(year1);
	printf("\n%s-%s-%s\n", C[count].start.day, C[count].start.month, C[count].start.year);
	printf("Input end day: ");
	char day2[3];
	gets_s(day2);
	char month2[3];
	gets_s(month2);
	char year2[5];
	gets_s(year2);
	C[count].end.day = _strdup(day2);
	C[count].end.month = _strdup(month2);
	C[count].end.year = _strdup(year2);
	printf("\n%s-%s-%s\n", C[count].end.day, C[count].end.month, C[count].end.year);
	printf("Input start hour: ");
	char hour1[3];
	char minute1[3];
	gets_s(hour1);
	gets_s(minute1);
	C[count].from.hour = _strdup(hour1);
	C[count].from.minute = _strdup(minute1);
	printf("%s:%s\n", C[count].from.hour, C[count].from.minute);
	printf("Input end hour: ");
	char hour2[3];
	char minute2[3];
	gets_s(hour2);
	gets_s(minute2);
	C[count].to.hour = _strdup(hour2);
	C[count].to.minute = _strdup(minute2);
	printf("%s:%s\n", C[count].to.hour, C[count].to.minute);
	printf("Input number of days in a week has this schedule: ");
	char dayc[2];
	gets_s(dayc);
	C[count].daysofWeek = _strdup(dayc);
	printf("%s", C[count].daysofWeek);
}

void removeCourse(schedule C[], int &numberofschedule)
{
	char  schedulecode[100];
	cin.ignore();
	printf("Input schedule code you need to change:");
	gets_s(schedulecode);
	int flag = 0;
	int count = 0;
	for (int i = 0; i < numberofschedule; i++)
	{
		if (strcmp(schedulecode, C[i].coursecode) == 0)
		{
			flag = 1;
			break;
		}
		count++;
	}
	if (flag == 0)
	{
		printf("schedule not found!");
		return;
	}
	else
		for (int i = count + 1; i < numberofschedule; i++)
		{
			std::swap(C[i].coursecode, C[i++].coursecode);
			std::swap(C[i].coursename, C[i++].coursename);
			std::swap(C[i].lecturername, C[i++].lecturername);
			std::swap(C[i].year.next, C[i++].year.next);
			std::swap(C[i].semester, C[i++].semester);
			std::swap(C[i].start.day, C[i++].start.day);
			std::swap(C[i].start.month, C[i++].start.month);
			std::swap(C[i].start.year, C[i++].start.year);
			std::swap(C[i].end.day, C[i++].end.month);
			std::swap(C[i].end.month, C[i++].end.month);
			std::swap(C[i].end.year, C[i++].end.year);
			std::swap(C[i].from.hour, C[i++].from.hour);
			std::swap(C[i].from.minute, C[i++].from.minute);
			std::swap(C[i].to.hour, C[i++].to.hour);
			std::swap(C[i].to.minute, C[i++].to.minute);
			std::swap(C[i].daysofWeek, C[i++].daysofWeek);
		}
	//
	numberofschedule--;
}

void printFile(schedule C[], int n)
{
	FILE *F = fopen("01.csv", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(F,"%s,%s,%s,%i,%i,%s/%s/%s,%s/%s/%s,%s:%s,%s:%s,%s", C[i].coursecode, C[i].coursename, C[i].lecturername, C[i].year.next,
			C[i].semester, C[i].start.day, C[i].start.month, C[i].start.year,
			C[i].end.day, C[i].end.month, C[i].end.year,
			C[i].from.hour, C[i].from.minute,
			C[i].to.hour, C[i].to.minute,
			C[i].daysofWeek);
	}
	fclose(F);
}