#ifndef BASICSTRUCT_H
#define BASICSTRUCT_H

#include <string>

enum UserType
{
	UserStudent = 0,
	UserAcademicStaff = 1,
	UserLecturer = 2
};

//struct Date
//{
//	unsigned year;
//	unsigned month;
//	unsigned day;
//};
//
//struct Time
//{
//	unsigned hour;
//	unsigned min;
//	unsigned sec;
//};

struct User
{
	std::string userName;
	std::string fullName;
	std::string email;
	std::string phoneNumber;
	UserType	userType;
	std::string hashedPass;
	std::string className;
};

struct Course
{
	std::string		courseCode;
	std::string		year;
	unsigned		semester;
	std::string		courseName;
	std::string		lecturerName;
	std::string		startDate;
	std::string		endDate;
	std::string		startTime;
	std::string		endTime;
	unsigned		dayOfWeek;
};

struct Presence
{
	std::string		courseCode;
	std::string		year;
	unsigned char	semester;
	std::string		studentId;
	unsigned char	week;
};

struct Score
{
	std::string		courseCode;
	std::string		year;
	unsigned char	semester;
	std::string		studentId;
	float			midtermScore;
	float			labScore;
	float			finalScore;
};

#endif // BASICSTRUCT_H
