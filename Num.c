#include "Num.h"
#include "Console.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <conio.h>


char ZiMo[ZIMO_MAX][300]={0};

void Num_load()
{
	int i=0,k=0;
	FILE *fp=0;
	char temp=0;
	char path[100]={0};
	char *p=0;
	for(i=0;i<ZIMO_MAX;i++)
	{
		temp=0;
		fp=0;
		sprintf(path,"Bitmap//Number//num-%d.txt",i);
		fp=fopen(path,"rt");
		if(fp==0)
		{
			printf("Error: %s 文件不存在或无法打开\n",path);
			exit(-1);
		}
		p=&ZiMo[i][0];
		while (temp!=EOF)
		{
			temp=fgetc(fp);
			*p=temp;
			p++;
		}
		fclose(fp);
	}
}
int getWeiNum(int value)
{
	int i=0;
	//获取位数
	while(value/(int)pow(10,i)!=0)
		i++;

	return i;
}
int getWei(int value, int result[MAX_NUM_W])
{
	int k=0,j=0;
	int wei=1;



	k=value;
	while(k>=10)
	{
		result[j++]=k%10;
		k=k/10;
		wei++;
	}
	result[j]=k;
/*
	for(i=0;i<wei;i++)
	{
		printf("%d\n",result[i]);
	}
*/
	return wei;
}
void Num_gen(long num,int x,int y,int mask)//mask为掩码位，按二进制对应位来掩码
{
	char temp=0;
	int wei=0,i=0,line=0;
	char *p=0;
	int result[MAX_NUM_W]={0};

	wei=getWei(num,result);//result中的数位逆序存放
	for(i=0;i<wei;i++)
	{
		temp=0;
		line=0;
		SetConsoleCursor(x+FONT_W*i,y);

		//取出当前位的字模数据，并作掩码处理，被掩的部分用字符X代替。X在字模库中的是第11个。
		p=ZiMo[(0x01<<i)&mask?11:result[wei-i-1]];
//p=ZiMo[11];
		//SetConsoleColor(7,1);
		while (temp!=EOF)
		{
			temp=*p;
			p++;
			if(temp=='\n')
			{
				line++;
				SetConsoleCursor(x+FONT_W*i,y+line);
			}else if(temp!=EOF)
				putchar(temp);
		}
	}
	if(wei>=MAX_NUM_W)
		return;

	//再写入一个空白字符以删除后一个数字（实现退格键）
	temp=0;
	line=0;
	SetConsoleCursor(x+FONT_W*i,y);
	p=ZiMo[10];	while (temp!=EOF)
	{
		temp=*p;
		p++;

		if(temp=='\n')
		{
			line++;
			SetConsoleCursor(x+FONT_W*i,y+line);
		}else if(temp!=EOF)
			putchar(temp);
	}
}
long Num_Comp(int num[MAX_NUM_W],int wei)
{
	long result=0;
	int i=0;

	for (i=0;i<=wei;i++)
	{
		result+=num[wei-i]*(int)pow(10,i);
	}
	return result;
}

int Num_input(int x,int y)
{
	char input=0;
	int num[MAX_NUM_W]={0};
	int i=0;
	while(1)
	{
		FlushInput();
		input=_getch();
//		printf("%d\n",input);
		if(input>=48 && input <=57)
		{
			if(i<MAX_NUM_W)
			{
				num[i++]=input-48;
			//	printf("%ld\n",Num_Comp(num,i));
				Num_gen(Num_Comp(num,i-1),x,y,0);
				
			}
		}else if(input==8)//退格键
		{
			if(i>0)
			{
				i--;
				num[i]=0;
			//	printf("%ld\n",Num_Comp(num,i-1));
				Num_gen(Num_Comp(num,i-1),x,y,0);
			}
		}else if(input==13)//回车键
		{
			return Num_Comp(num,i-1);
		}

	}
	return 0;
}   