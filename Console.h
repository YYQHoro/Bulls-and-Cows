#ifndef __CURSOR_H__
#define __CURSOR_H__
#include <windows.h>   
#include <windef.h>
void Con_init();

void Cur_SetVisiable(int visible);
void Cur_SetSize(int size);
unsigned long Con_fill(int x,int y,int len,char dat);
void SetConsoleCursor(int x,int y);
void SetConsoleColor(int front,int background);
COORD GetConsoleCursor(int x,int y);
void ShowMessage(char* text);
void FlushInput();
/*
 FOREGROUND_BLUE      0x0001 // text color contains blue.

 FOREGROUND_GREEN     0x0002 // text color contains green.

 FOREGROUND_RED       0x0004 // text color contains red.

 FOREGROUND_INTENSITY 0x0008 // text color is intensified.高亮颜色

背景颜色使用如下组合（其实就是上面值*0x10）：

 BACKGROUND_BLUE      0x0010 // background color contains blue.

 BACKGROUND_GREEN     0x0020 // background color contains green.

 BACKGROUND_RED       0x0040 // background color contains red.

 BACKGROUND_INTENSITY 0x0080 // background color is intensified.

 FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE 7,0
*/

#endif