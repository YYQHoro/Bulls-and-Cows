#include "Ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
int Rank_getLastIndex(int level)
{
	FILE *fp=0;
	int score[20]={0};
	int index[20]={0};
	int i=0,max_index_i=0;
	switch(level)
	{
	case 0:
		fp=fopen(PATH_LIST_SIMPLE,"r");
		break;
	case 1:
		fp=fopen(PATH_LIST_NORMAL,"r");
		break;
	case 2:
		fp=fopen(PATH_LIST_GOD,"r");
		break;
	default:
		break;
	}
	if(fp==0)
	{
		printf("Error: 排行榜，文件不存在或无法打开，Level=%d\n",level);
		exit(-1);
	}
	for(i=0;i<MAX_RECORD;i++)
	{
		fscanf(fp,"%d,%d\n",index+i,score+i);

		//以索引（场次）的最大值为准定位到上一次的比赛结果
		if(index[max_index_i]<index[i])
			max_index_i=i;
	}
	fclose(fp);
	return index[max_index_i];
}
void Rank_new(int level,int mark)
{
	FILE *fp=0;
	int score[20]={0};
	int index[20]={0};
	int max_index_i=-1;
	int i=0;

	//以读方式打开读入全部游戏记录
	switch(level)
	{
	case 0:
		fp=fopen(PATH_LIST_SIMPLE,"r");
		break;
	case 1:
		fp=fopen(PATH_LIST_NORMAL,"r");
		break;
	case 2:
		fp=fopen(PATH_LIST_GOD,"r");
		break;
	default:
		break;
	}
	if(fp==0)
	{
		printf("Error: 排行榜，文件不存在或无法打开，Level=%d\n",level);
		exit(-1);
	}

	for(i=0;i<MAX_RECORD;i++)
	{
		fscanf(fp,"%d,%d\n",index+i,score+i);
//		printf("%d\n",score[i]);
		if(index[i]==0 && i==0)//最开始文件中没有任何内容的时候
		{
			max_index_i=-1;
			break;
		}
		//以索引（场次）的最大值为准定位到上一次的比赛结果
		if(index[max_index_i]<index[i])
			max_index_i=i;
	}
	fclose(fp);
//	printf("\n");

	//以写方式打开并清空文件所有数据
	switch(level)
	{
	case 0:
		fp=fopen(PATH_LIST_SIMPLE,"wt");
		break;
	case 1:
		fp=fopen(PATH_LIST_NORMAL,"wt");
		break;
	case 2:
		fp=fopen(PATH_LIST_GOD,"wt");
		break;
	default:
		break;
	}
	
	//若记录已满，重写第一条记录
	//将场次加一并和比赛结果写入下一条记录
	index[max_index_i+1<MAX_RECORD?max_index_i+1:0]=index[max_index_i==-1?0:max_index_i]+1;
	score[max_index_i+1<MAX_RECORD?max_index_i+1:0]=mark;
	
	//回写文件
	for(i=0;i<MAX_RECORD;i++)
	{
		fprintf(fp,"%d,%d\n",index[i],score[i]);
//		printf("%d\n",score[i]);
	}
	fclose(fp);

}
void Rank_list()
{

	FILE *fp=0;
	int index[3][20]={0};
	int score[3][20]={0};
	int i=0,level=0;
	int j=0,k=0;
	int last_index[3]={0};
	int recent_index[3]={0};

	char temp[10]={0};

	for(level=0;level<3;level++)
	{
		//取得每个难度下上一次比赛的场次，此数据将在排行榜中凸显
		recent_index[level]=Rank_getLastIndex(level);
	}

	for(level=0;level<3;level++)
	{
		switch(level)
		{
		case 0:
			fp=fopen(PATH_LIST_SIMPLE,"rt");
			break;
		case 1:
			fp=fopen(PATH_LIST_NORMAL,"rt");
			break;
		case 2:
			fp=fopen(PATH_LIST_GOD,"rt");
			break;
		default:
			return;
		}
		if(fp==0)
		{
			printf("Error: 排行榜，文件不存在或无法打开，Level=%d\n",level);
			exit(-1);
		}
		for(i=0;i<MAX_RECORD;i++)
		{
			fscanf(fp,"%d,%d\n",index[level]+i,score[level]+i);
//			printf("%d,%d\n",index[level][i],score[level][i]);
		}

//		printf("\n");
		for(i=0;i<MAX_RECORD;i++)
		{
			for(j=i+1;j<MAX_RECORD;j++)
			{
				if(score[level][i]>score[level][j])//回合数从小到大排序
				{
					k=score[level][i];
					score[level][i]=score[level][j];
					score[level][j]=k;

					k=index[level][i];
					index[level][i]=index[level][j];
					index[level][j]=k;
				}
			}
		}
		fclose(fp);
	}
/*
		for(i=0;i<20;i++)
		{
			printf("%d,%d\n",index[level][i],score[level][i]);
		}
*/
	system("cls");
	system("color 2F");
	putchar('\n');
	putchar('\n');
	fp=fopen(PATH_LIST,"rt");
	if(fp==0)
	{
		printf("Error: %s 文件不存在或无法打开\n",PATH_LIST);
		exit(-1);
	}
	//setConsoleCursor(0,0);
	i=0;
	while (i!=EOF)
	{
		putchar(i);
		i=fgetc(fp);
	}
	fclose(fp);



	//总共MAX_RECORD行数据
	for(i=0;i<MAX_RECORD;i++)
	{
		printf("\t\t║");
		//一行里面有三列，分别是简单难度，普通难度，大神难度
		for(j=0;j<3;j++)
		{
			//每一列数据有MAX_RECORD项，此处单独处理每一列数据是要忽略没有记录的项，同时跳过已打印出来的项
			for(k=i;k<MAX_RECORD;k++)
			{
				//以数组索引从小到大依据跳过已打印的项。没有记录的项的index（比赛场次）为0
				if(index[j][k]==0 || k<=last_index[j])
				{
					continue;
				}else{
					last_index[j]=k;
					printf("  ");

					if(recent_index[j]==index[j][k])
						SetConsoleColor(HIGHT_LIGHT_F,HIGHT_LIGHT_B);
					printf("%d",index[j][k]);

					SetConsoleColor(NORMAL_LIGHT_F,NORMAL_LIGHT_B);
					printf("\t\t  ");

					if(recent_index[j]==index[j][k])
						SetConsoleColor(HIGHT_LIGHT_F,HIGHT_LIGHT_B);
					printf("%d",score[j][k]);
					
					SetConsoleColor(NORMAL_LIGHT_F,NORMAL_LIGHT_B);
					printf("\t║");


					SetConsoleColor(NORMAL_LIGHT_F,NORMAL_LIGHT_B);//恢复默认

					//printf("  %d\t\t  %d\t║",index[j][k],score[j][k]);

					break;
				}
			}
			//全部遍历完了还没有发现要打印的项，则打印空行
			if(k==MAX_RECORD)
			{
				printf("  %c\t\t  %c\t║",' ',' ');
			}
		}
		putchar('\n');
	}
	printf("		╚═══════════╩═══════════╩═══════════╝");

	printf("\n红色高亮的是您最近的挑战记录。输入代码c1，c2，c3，ca加回车可分别清除简单难度，普通难度，大神难度，和所有难度的记录\n\t\t\t\t\t\t\t\t\t\t\t输入q加回车退回主菜单\n");
	do
	{
		scanf("%s",temp);
		if(strcmp(temp,"q")==0)
		{
			break;
		}else if(strcmp(temp,"c1")==0)
		{
			Rank_clear(0);
			printf("简单难度的记录已被清空，");
			system("pause");
			Rank_list();
			break;
		}else if(strcmp(temp,"c2")==0)
		{
			Rank_clear(1);
			printf("普通难度的记录已被清空，");
			system("pause");
			Rank_list();
			break;
		}else if(strcmp(temp,"c3")==0)
		{
			Rank_clear(2);
			printf("大神难度的记录已被清空，");
			system("pause");
			Rank_list();
			break;
		}else if(strcmp(temp,"ca")==0)
		{
			Rank_clear(-1);
			printf("所有难度的记录已被清空，");
			system("pause");
			Rank_list();
			break;
		}
	}while(1);
}

//当参数level的值为-1时，清除三个难度游戏的所有记录
void Rank_clear(int level)
{
	FILE *fp=0;
	int i=0;
	if(level==-1)
	{
		for(i=0;i<3;i++)
		{
			switch(i)
			{
			case 0:
				fp=fopen(PATH_LIST_SIMPLE,"wt");
				break;
			case 1:
				fp=fopen(PATH_LIST_NORMAL,"wt");
				break;
			case 2:
				fp=fopen(PATH_LIST_GOD,"wt");
				break;
			default:
				return;
			}

			if(fp==0)
			{
				printf("Error: 排行榜，文件不存在或无法打开，Level=%d\n",i);
				exit(-1);
			}
		}
	}else
	{
		switch(level)
		{
		case 0:
			fp=fopen(PATH_LIST_SIMPLE,"wt");
			break;
		case 1:
			fp=fopen(PATH_LIST_NORMAL,"wt");
			break;
		case 2:
			fp=fopen(PATH_LIST_GOD,"wt");
			break;
		default:
			return;
		}
	}
	if(fp==0)
	{
		printf("Error: 排行榜，文件不存在或无法打开，Level=%d\n",level);
		exit(-1);
	}
	fclose(fp);
}