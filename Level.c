#include "Level.h"
#include "Console.h"
#include "Animation.h"
#include "Num.h"
#include "Ranking.h"
#include "MusicManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACK 8

#define CHOOSE_CHAR "�{��ߩרTһ"
#define CHOOSE_NONE "            "

int Level_choose()
{
	int i=0;
	int index=0;
	int key=0;

	system("color 2F");

	Ani_Main();
	Ani_Level();

	SetConsoleCursor(29,15);


	printf(CHOOSE_CHAR);

	while(1)
	{
		FlushInput();

		key=_getch();
		if(key==224)
		{
			key=_getch();
			if(key==KEY_UP)
			{
				Music_Choose();
				SetConsoleCursor(29,15+index*2);
				printf(CHOOSE_NONE);
				index=index==0?6:index-1;
				SetConsoleCursor(29,15+index*2);
				printf(CHOOSE_CHAR);
			}
			else if(key==KEY_DOWN)
			{
				Music_Choose();
				SetConsoleCursor(29,15+index*2);
				printf(CHOOSE_NONE);
				index=index==6?0:index+1;
				SetConsoleCursor(29,15+index*2);
				printf(CHOOSE_CHAR);
			}
			
		}else if(key==KEY_ENTER)
		{
			Music_Confirm();
			for(i=0;i<15;i++)
			{
				SetConsoleColor(i,2);
				SetConsoleCursor(29,15+index*2);
				printf(CHOOSE_CHAR);
				_sleep(100);
			}

			SetConsoleColor(0,0);
			SetConsoleCursor(0,0);
			for(i=0;i<110*34;i++)
			{
				putchar(' ');
			}
			//system("cls");
			if(index==6)
				exit(0);
			else
				return index;
		}else if(key==KEY_ESC)
		{
			exit(0);
		}
	}
	return 0;
}
int Level_simple()
{

	int input=0;
	int input_dis[MAX_NUM_W]={0};
	int target_dis[MAX_NUM_W]={0};

	int input_weishu=4;
	int target=0,mask=0;
	int round=0;
	int i=0;

	system("color 3F");
	system("MODE con: COLS=120 LINES=34");
	
	//ȷ���������λ��
	
	while(1)
	{	
		system("cls");
		SetConsoleCursor(0,0);
		Ani_basic_print(PATH_SIMPLE_1,0);
		input_weishu=Num_input(0,16);//y=18�������˻��ֵ�BUG����Ϊ��ӡ�����ַ���ϵͳ�Զ�����

		if(input_weishu>5)
			ShowMessage("������λ���ˣ��㻹�ǲ�Ҫ����ô��ɣ���Ȼ���úܲҡ���");
		else if(input_weishu==0)
			ShowMessage("λ����Ȼ��0���㻹�벻��������");
		else
		{
			break;
		}
	}


	//����ָ��λ���������
	srand((int)time(0));
	do{
		target=rand()%(int)pow(10,input_weishu);
	}while(getWeiNum(target)!=input_weishu);

	mask=0x1F>>(5-input_weishu);

	getWei(target,target_dis);

	system("cls");

	
	for(round=0;round<MAX_ROUND_SIMPLE;round++)
	{
		SetConsoleCursor(0,0);
		printf("�²¿��� <(������)/ %sʣ��غ���:%d",input==0?"":target-input>0?"��ǰ������Ŀ����С��":"��ǰ������Ŀ������",MAX_ROUND_SIMPLE-round);
		Num_gen(target,0,1,mask);
		_getch();
		system("cls");
		printf("�²¿��� <(������)/ %sʣ��غ���:%d",input==0?"":target-input>0?"��ǰ������Ŀ����С��":"��ǰ������Ŀ������",MAX_ROUND_SIMPLE-round);
		Num_gen(target,0,1,mask);
		input=Num_input(0,18);
		getWei(input,input_dis);
		for(i=input_weishu-1;i>=0;i--)
		{
			if(input_dis[i]==target_dis[i])
				mask&=~(0x01<<(input_weishu-i-1));
		}
		if(mask==0)
		{
			system("cls");
			SetConsoleCursor(0,0);
			printf("�����Ρ��򵥡�������ս�ǵ�%d�����˴���ս����%d�غϣ���������ص����˵�����¼�˴β����ֽ��\n", Rank_getLastIndex(0)+1,round);
			
			Music_Win();
			Ani_Win();
			FlushInput();
			_getch();

			return round;
		}
		
	}
	if(round==MAX_ROUND_SIMPLE)
	{
		Music_Lose();
		Ani_Lose();
		FlushInput();
		_getch();
	}

	return 0;
}
int Level_normal()
{
	int input=0;

	int input_weishu=4;
	int target=0,mask=0;
	int round=0;
	int i=0;

	double temp=0;
	system("color 3F");
	system("MODE con: COLS=120 LINES=34");
	
	//ȷ���������λ��
	
	while(1)
	{	
		system("cls");
		SetConsoleCursor(0,0);
		Ani_basic_print(PATH_SIMPLE_1,0);
		input_weishu=Num_input(0,16);//y=18�������˻��ֵ�BUG����Ϊ��ӡ�����ַ���ϵͳ�Զ�����

		if(input_weishu>5)
			ShowMessage("������λ���ˣ��㻹�ǲ�Ҫ����ô��ɣ���Ȼ���úܲҡ���");
		else if(input_weishu==0)
			ShowMessage("λ����Ȼ��0���㻹�벻��������");
		else
		{
			break;
		}
	}

	//����ָ��λ���������
	srand((int)time(0));
	do{
		target=rand()%(int)pow(10,input_weishu);
	}while(getWeiNum(target)!=input_weishu);

	system("cls");
	round=0;
	do 
	{
		SetConsoleCursor(0,0);
		if(round)
		{
			system("cls");

			printf("�²¿��� <(������)/  ʣ��غ���:%d����ǰ������Ŀ����%s����Ŀ������Լ����", MAX_ROUND_NORMAL-round,target-input>0?"С":"��");

			i=abs(target-input+rand()%10);//(int)pow(10,getWeiNum(abs(target-input)))));

			Num_gen(i,0,1,0);
			Num_gen(input,0,18,0);
			_getch();
			system("cls");
			//printf("�²¿��� <(������)/ %d,ʣ��غ���:%d,��Ŀ������Լ����", target,MAX_ROUND_NORMAL-round);
			printf("�²¿��� <(������)/  ʣ��غ���:%d����ǰ������Ŀ����%s����Ŀ������Լ����", MAX_ROUND_NORMAL-round,target-input>0?"С":"��");
			Num_gen(i,0,1,0);
		}else{
			printf("�Ȳ²¿��� <(������)/   ʣ��غ���:%d", MAX_ROUND_NORMAL-round);
			Num_gen(target,0,1,0x1F);
		}
		
		input=Num_input(0,18);

		if(input==target)
		{
			system("cls");
			SetConsoleCursor(0,0);
			printf("�����Ρ���ͨ��������ս�ǵ�%d�����˴���ս����%d�غϣ���������ص����˵�����¼�˴β����ֽ��\n", Rank_getLastIndex(1)+1,round);

			Music_Win();
			Ani_Win();
			FlushInput();
			_getch();

			return round;
		}

		
		round++;
	}while(round<MAX_ROUND_NORMAL);

	if(round==MAX_ROUND_NORMAL)
	{
		Music_Lose();
		Ani_Lose();
		FlushInput();
		_getch();
		
	}
	
	return 0;
}
int Level_god()
{
	int input=0;

	int input_weishu=4;
	int target=0,mask=0;
	int round=0;
	int i=0;

	double temp=0;
	system("color 3F");
	system("MODE con: COLS=120 LINES=34");
	
	

	//���������
	srand((int)time(0));
	
	target=rand()%10000;
	
	system("cls");

	round=1;
	do 
	{
		SetConsoleCursor(0,0);

		printf("�²¿��� <(������)/  ���ûغ���:%d��%s��ʱ��Q�����Է�����Ϸ", round,input==0?"":target-input>0?"��ǰ������Ŀ����С��":"��ǰ������Ŀ������");
		
		Num_gen(target,0,1,0x1F);
		
		FlushInput();
		if(_getch()==113)
		{
			break;
		}

		system("cls");
			
		printf("�²¿��� <(������)/  ���ûغ���:%d%s", round,input==0?"":target-input>0?"����ǰ������Ŀ����С":"����ǰ������Ŀ������");
		Num_gen(target,0,1,0x1F);
		
		
		input=Num_input(0,18);

		if(input==target)
		{
			system("cls");
			SetConsoleCursor(0,0);
			printf("�����Ρ����񡿼�����ս�ǵ�%d�����˴���ս����%d�غϣ���������ص����˵�����¼�˴β����ֽ��\n", Rank_getLastIndex(2)+1,round);

			Music_Win();
			Ani_Win();
			FlushInput();
			_getch();
			return round;
		}

		round++;
	}while(1);


	if(round==MAX_ROUND_GOD)
	{
		Music_Lose();
		Ani_Lose();
		FlushInput();
		_getch();
	}


	return 0;

}