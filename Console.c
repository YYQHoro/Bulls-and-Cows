#include "Console.h"

#include <windows.h>   
#include <windef.h>

HANDLE handle_out=0;
HANDLE handle_in=0;
HWND   hWnd;
//CONSOLE_SCREEN_BUFFER_INFO bInfo;
void FlushInput()
{
	FlushConsoleInputBuffer(handle_in);
}
void ShowMessage(char* text)
{

	MessageBox(hWnd,text, "温馨提示：",MB_ICONINFORMATION| MB_OK);
}

void Con_init()
{
	handle_out=GetStdHandle(STD_OUTPUT_HANDLE);	//获得标准输出设备句柄
	handle_in=GetStdHandle(STD_INPUT_HANDLE);//获得标准输入设备句柄
	hWnd=FindWindow("ConsoleWindowClass",NULL);//获取当前控制台的窗口句柄
	//GetConsoleScreenBufferInfo(hOut, &bInfo );
}
COORD GetConsoleCursor(int x,int y)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(handle_out, &bInfo);
	return bInfo.dwCursorPosition;
}
void SetConsoleCursor(int x,int y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(handle_out, pos);
}
void SetConsoleColor(int front,int background)
{
    SetConsoleTextAttribute(handle_out, (unsigned short)((background*0x10)+front));
}
unsigned long Con_fill(int x,int y,int len,char dat)
{
	unsigned long result;
	COORD pos = {x, y};
	FillConsoleOutputCharacter(handle_out,dat,len, pos, &result);
//	WriteConsoleOutputCharacter(handle_out, &dat, 1, pos,  &result);
	return result;
}
unsigned long Con_puts(int x,int y,int len,char dat)
{
	unsigned long result;
	COORD pos = {x, y};
	FillConsoleOutputCharacter(handle_out,dat,len, pos, &result);
	return result;
}
void Cur_SetVisiable(int visible)
{
    //定义光标信息结构体
	CONSOLE_CURSOR_INFO cci;
	//获得当前光标信息
    GetConsoleCursorInfo(handle_out, &cci);        

    cci.bVisible=visible;    
	
	SetConsoleCursorInfo(handle_out, &cci);  

}
void Cur_SetSize(int size)
{
    //定义光标信息结构体
	CONSOLE_CURSOR_INFO cci;
	//获得当前光标信息
    GetConsoleCursorInfo(handle_out, &cci);        
	
	cci.dwSize=size; 
	
	SetConsoleCursorInfo(handle_out, &cci);  

}

