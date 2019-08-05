#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MusicManager.h"
#include "Animation.h"
#include "Console.h"
#include "Net.h"
#include "Level.h"
#include "Num.h"
#include "Ranking.h"

int ctrlhandler(DWORD type);

int main()
{
	char i=0;
	int level=0;
	Con_init();	
	Cur_SetVisiable(0);

	Music_Welcome();


	SetConsoleCtrlHandler((PHANDLER_ROUTINE) ctrlhandler, 1);

	Num_load();
	system("title ��������Ϸ Version 1.0  Copyright (C)2016 1500850226 ������ ��Ȩ����");
	system("MODE con: COLS=110 LINES=34");

	Ani_Logo();

	Ani_Author();

//	NetConnect("192.168.1.255");
	
	while(1)
	{
		FlushInput();
		system("color 2F");

		i=Level_choose();
		//mciSendString("stop bgm", NULL, 0, NULL); //ֹͣ����bgm
		switch(i)
		{
		case 0://���Ѷ�
			Rank_new(i,Level_simple());
			system("MODE con: COLS=110 LINES=34");
			break;
		case 1://��ͨ�Ѷ�
			Rank_new(i,Level_normal());
			system("MODE con: COLS=110 LINES=34");
			break;
		case 2://�����Ѷ�
			Rank_new(i,Level_god());
			system("MODE con: COLS=110 LINES=34");
			break;
		case 3://���а�
			Rank_list();
			break;
		case 4://����
			break;
		case 5://��Ϸ˵��
			Ani_Help();
			break;
		case 6://�˳�
		default:
			Ani_Exit();
			return 0;
		}
		//mciSendString("play bgm",NULL,0,NULL);
	}
	return 0;
}
int ctrlhandler(DWORD type)
{
	static int exiting=0;
	switch(type)
	{
		case CTRL_C_EVENT:
			if(!exiting)
			{
				system("MODE con: COLS=110 LINES=34");
				Ani_Exit();
			}
			exiting=1;
			return 1;
		case CTRL_CLOSE_EVENT: 
			if(!exiting)
			{
				system("MODE con: COLS=110 LINES=34");
				Ani_Exit();
			}
			exiting=1;
			return 1;
		default:
			return 0;
       
	}
	
	return 0;//1��ֹ�ر�
}