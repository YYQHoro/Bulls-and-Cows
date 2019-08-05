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
	system("title 猜数字游戏 Version 1.0  Copyright (C)2016 1500850226 杨宇庆 版权所有");
	system("MODE con: COLS=110 LINES=34");

	Ani_Logo();

	Ani_Author();

//	NetConnect("192.168.1.255");
	
	while(1)
	{
		FlushInput();
		system("color 2F");

		i=Level_choose();
		//mciSendString("stop bgm", NULL, 0, NULL); //停止播放bgm
		switch(i)
		{
		case 0://简单难度
			Rank_new(i,Level_simple());
			system("MODE con: COLS=110 LINES=34");
			break;
		case 1://普通难度
			Rank_new(i,Level_normal());
			system("MODE con: COLS=110 LINES=34");
			break;
		case 2://大神难度
			Rank_new(i,Level_god());
			system("MODE con: COLS=110 LINES=34");
			break;
		case 3://排行榜
			Rank_list();
			break;
		case 4://联机
			break;
		case 5://游戏说明
			Ani_Help();
			break;
		case 6://退出
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
	
	return 0;//1阻止关闭
}