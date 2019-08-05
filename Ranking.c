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
		printf("Error: ���а��ļ������ڻ��޷��򿪣�Level=%d\n",level);
		exit(-1);
	}
	for(i=0;i<MAX_RECORD;i++)
	{
		fscanf(fp,"%d,%d\n",index+i,score+i);

		//�����������Σ������ֵΪ׼��λ����һ�εı������
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

	//�Զ���ʽ�򿪶���ȫ����Ϸ��¼
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
		printf("Error: ���а��ļ������ڻ��޷��򿪣�Level=%d\n",level);
		exit(-1);
	}

	for(i=0;i<MAX_RECORD;i++)
	{
		fscanf(fp,"%d,%d\n",index+i,score+i);
//		printf("%d\n",score[i]);
		if(index[i]==0 && i==0)//�ʼ�ļ���û���κ����ݵ�ʱ��
		{
			max_index_i=-1;
			break;
		}
		//�����������Σ������ֵΪ׼��λ����һ�εı������
		if(index[max_index_i]<index[i])
			max_index_i=i;
	}
	fclose(fp);
//	printf("\n");

	//��д��ʽ�򿪲�����ļ���������
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
	
	//����¼��������д��һ����¼
	//�����μ�һ���ͱ������д����һ����¼
	index[max_index_i+1<MAX_RECORD?max_index_i+1:0]=index[max_index_i==-1?0:max_index_i]+1;
	score[max_index_i+1<MAX_RECORD?max_index_i+1:0]=mark;
	
	//��д�ļ�
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
		//ȡ��ÿ���Ѷ�����һ�α����ĳ��Σ������ݽ������а���͹��
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
			printf("Error: ���а��ļ������ڻ��޷��򿪣�Level=%d\n",level);
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
				if(score[level][i]>score[level][j])//�غ�����С��������
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
		printf("Error: %s �ļ������ڻ��޷���\n",PATH_LIST);
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



	//�ܹ�MAX_RECORD������
	for(i=0;i<MAX_RECORD;i++)
	{
		printf("\t\t�U");
		//һ�����������У��ֱ��Ǽ��Ѷȣ���ͨ�Ѷȣ������Ѷ�
		for(j=0;j<3;j++)
		{
			//ÿһ��������MAX_RECORD��˴���������ÿһ��������Ҫ����û�м�¼���ͬʱ�����Ѵ�ӡ��������
			for(k=i;k<MAX_RECORD;k++)
			{
				//������������С�������������Ѵ�ӡ���û�м�¼�����index���������Σ�Ϊ0
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
					printf("\t�U");


					SetConsoleColor(NORMAL_LIGHT_F,NORMAL_LIGHT_B);//�ָ�Ĭ��

					//printf("  %d\t\t  %d\t�U",index[j][k],score[j][k]);

					break;
				}
			}
			//ȫ���������˻�û�з���Ҫ��ӡ������ӡ����
			if(k==MAX_RECORD)
			{
				printf("  %c\t\t  %c\t�U",' ',' ');
			}
		}
		putchar('\n');
	}
	printf("		�^�T�T�T�T�T�T�T�T�T�T�T�m�T�T�T�T�T�T�T�T�T�T�T�m�T�T�T�T�T�T�T�T�T�T�T�a");

	printf("\n��ɫ�����������������ս��¼���������c1��c2��c3��ca�ӻس��ɷֱ�������Ѷȣ���ͨ�Ѷȣ������Ѷȣ��������Ѷȵļ�¼\n\t\t\t\t\t\t\t\t\t\t\t����q�ӻس��˻����˵�\n");
	do
	{
		scanf("%s",temp);
		if(strcmp(temp,"q")==0)
		{
			break;
		}else if(strcmp(temp,"c1")==0)
		{
			Rank_clear(0);
			printf("���Ѷȵļ�¼�ѱ���գ�");
			system("pause");
			Rank_list();
			break;
		}else if(strcmp(temp,"c2")==0)
		{
			Rank_clear(1);
			printf("��ͨ�Ѷȵļ�¼�ѱ���գ�");
			system("pause");
			Rank_list();
			break;
		}else if(strcmp(temp,"c3")==0)
		{
			Rank_clear(2);
			printf("�����Ѷȵļ�¼�ѱ���գ�");
			system("pause");
			Rank_list();
			break;
		}else if(strcmp(temp,"ca")==0)
		{
			Rank_clear(-1);
			printf("�����Ѷȵļ�¼�ѱ���գ�");
			system("pause");
			Rank_list();
			break;
		}
	}while(1);
}

//������level��ֵΪ-1ʱ����������Ѷ���Ϸ�����м�¼
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
				printf("Error: ���а��ļ������ڻ��޷��򿪣�Level=%d\n",i);
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
		printf("Error: ���а��ļ������ڻ��޷��򿪣�Level=%d\n",level);
		exit(-1);
	}
	fclose(fp);
}