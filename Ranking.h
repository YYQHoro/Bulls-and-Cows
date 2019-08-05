#ifndef __RANKING_H__
#define __RANKING_H__

void Rank_list();
void Rank_new(int level,int score);
void Rank_clear(int level);
int Rank_getLastIndex(int level);

#define PATH_LIST "RankingList//RankingList.txt"
#define PATH_LIST_SIMPLE "RankingList//simple.txt"
#define PATH_LIST_NORMAL "RankingList//normal.txt"
#define PATH_LIST_GOD "RankingList//god.txt"

#define HIGHT_LIGHT_F 12
#define HIGHT_LIGHT_B 2
#define NORMAL_LIGHT_F 15
#define NORMAL_LIGHT_B 2

#define MAX_RECORD 20 //最大记录数

#endif