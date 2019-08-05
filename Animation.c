#include "Animation.h"
#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
void Ani_Exit()
{
	int i=0;
	SetConsoleColor(7,0);
	system("cls");
//	system("MODE con: COLS=120 LINES=34");
	Ani_basic_print(PATH_EXIT,0);
	_sleep(1000);

	for(i=0;i<30;i++)
	{
		_sleep(50);
		putchar('\n');
	}
	Ani_Author();
	_sleep(2000);
}
void Ani_Help()
{
	system("cls");
	system("color 2F");
	Ani_basic_print(PATH_HELP,0);
	system("pause");
}
void Ani_Lose()
{
//	system("cls");
	system("color 0c");
	Ani_basic_print(PATH_LOSE,0);
}
void Ani_Win()
{
//	system("cls");
	system("color 0a");
	Ani_basic_print(PATH_WIN,0);
}
void Ani_Level()
{
	Ani_basic_print(PATH_LEVEL,DELAY_LINE);
}
void Ani_Main()
{
	char i;
	system("cls");
	Ani_basic_print(PATH_MAIN,DELAY_LINE);
	for(i=0;i<55;i++)
	{
		_sleep(50);
		printf("☆");
	}
	putchar('\n');
}
void Ani_Author()
{
	char i;
	SetConsoleColor(2+8,0);

	Ani_basic_print(PATH_AUTHOR,DELAY_LINE);
	for(i=0;i<4;i++)
	{
		_sleep(DELAY_LINE);
		putchar('\n');
	}
	_sleep(1000);

	for(i=0;i<35;i++)
	{
		_sleep(DELAY_LINE);
		putchar('\n');
	}

}
void Ani_Logo()
{
	char i=0;
	
	//system("color 2F");

	system("cls");
	SetConsoleColor(7,0);

	
	Ani_basic_print(PATH_LOGO,DELAY_LINE);

	_sleep(1000);

	for(i=0;i<30;i++)
	{
		_sleep(DELAY_LINE);
		putchar('\n');
	}

}
void Ani_basic_print(char * addr,int delay)
{
	FILE *fp=0;
	char temp=0;
	fp=fopen(addr,"rt");
	if(fp==0)
	{
		printf("Error: %s 文件不存在或无法打开\n",addr);
		exit(-1);
	}

	while (temp!=EOF)
	{
		putchar(temp);
		temp=fgetc(fp);
		if(temp=='\n')
		{
			_sleep(delay);
		}
	}
	fclose(fp);
}