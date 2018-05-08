#ifndef MISC_H
#define MISC_H

#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <list>
#include <stdio.h>

#include "basicstruct.h"
#include "md5hash.h"
#include "rectangle.h"

#define CURSOR_GOTOXY(x, y) gotoxy(x - 1, y - 1)
#define CLEAR_CMD() setColor(COLOR_BLACK, COLOR_DEFAULT); std::system("CLS"); setColor(COLOR_BLACK, COLOR_DEFAULT);

#define COLOR_BLACK 0
#define COLOR_DEFAULT 7
#define COLOR_GRAY 8
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_STEAL 11
#define COLOR_RED 12
#define COLOR_PINK 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

typedef std::vector<std::string> vecStr;
typedef std::vector<std::vector<std::string>> vecStr2D;

void getConsoleSize(int &rows, int &cols);
void gotoxy(int x, int y);
void setBgColor(WORD color);
void setFgColor(WORD color);
void setColor(WORD bgColor, WORD fgColor);
std::string getPassword(std::string text, int y, bool useFake);
void loginField(std::string &, std::string &);
void changePassField(std::string &, std::string &, std::string &);

void showStatus(std::string status, int x, int y, int w, int h);

void strToUpper(std::string &str);
User vecToUser(vecStr);

std::string intToDay(int);
#endif // MISC_H