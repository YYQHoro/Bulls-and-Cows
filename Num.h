#ifndef __NUM_H__
#define __NUM_H__

#define MAX_NUM_W 6
#define ZIMO_MAX 12
#define FONT_W 16
#define FONT_H 16

void Num_gen(long num,int x,int y,int mask);
int getWei(int value, int result[MAX_NUM_W]);
int Num_input(int x,int y);
long Num_Comp(int num[MAX_NUM_W],int wei);
void Num_load();
int getWeiNum(int value);
#endif