#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>


struct scoreboard
{
	char *name;
	char *classname;
	int mid;
	int labcount;
	int bonuscount;
	int finalcount;
};

void inputScoreboard(scoreboard S[], int total);
void editScoreboard(scoreboard S[], int total);
void printScoreboard(scoreboard S[], int total);
