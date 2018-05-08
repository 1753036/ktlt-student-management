#include "Scoreboard.h"


void inputScoreboard(scoreboard S[], int total)
{
	int midterm, final, lab, bonus;
	int number;
	for (int i = 0; i <= total-1; i++)
	{
		char c;
		scanf("%c", &c);
		printf("Input student's name:");
		char name[50];
		gets_s(name);
		S[i].name = _strdup(name);
		puts(S[i].name);
		printf("Input student's classname: ");
		char nameclass[7];
		gets_s(nameclass);
		S[i].classname = _strdup(nameclass);
		printf("Input grade in midterm: ");
		scanf("%i", &midterm);
		S[i].mid = midterm;
		printf("Input grade in final: ");
		scanf("%i", &final);
		S[i].finalcount = final;
		printf("Input grade in lab: ");
		scanf("%i", &lab); 
		S[i].labcount = lab;
		printf("Input grade in bonus: ");
		scanf("%i", &bonus); 
		S[i].bonuscount = bonus;
	}
}

void editScoreboard(scoreboard S[], int total)
{
	char name[50];
	int bonus, midterm, final, lab;
	char c;
	scanf("%c", &c);
	printf("Input student's name: ");
	gets_s(name);
	int flag = 0;
	for (int i = 0; i < total; i++)
	{
		if (strcmp(S[i].name, name) == 0)
		{
			flag = 1;
			printf("Input grade in midterm: ");
			scanf("%i", &midterm);
			S[i].mid = midterm;
			printf("Input grade in final: ");
			scanf("%i", &final);
			S[i].finalcount = final;
			printf("Input grade in lab: ");
			scanf("%i", &lab);
			S[i].labcount = lab;
			printf("Input number of columns in bonus: ");
			scanf("%i", &bonus);
			S[i].bonuscount = bonus;
		}
	}
	if (flag == 0)
	{
		printf("Not found!");
		return;
	}
}

void printScoreboard(scoreboard S[], int total)
{
	for (int i = 0; i <= total-1; i++)
	{
		printf("\nName:%s Class:%s", S[i].name, S[i].classname);
		printf("\nMidterm grade: %i", S[i].mid);
		printf("\nLab grade: %i", S[i].labcount);
		printf("\nFinal grade: %i",S[i].finalcount);
		printf("\nBonus grade: %i",S[i].bonuscount);
	}
}