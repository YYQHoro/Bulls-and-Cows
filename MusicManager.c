#include "MusicManager.h"
#include <windows.h>
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>
//SND_LOOP
void Music_Welcome()
{
	/*
	unsigned FREQUENCY[] = {392,392,440,392,523,494,  
              392,392,440,392,587,523,  
              392,392,784,659,523,494,440,  
              689,689,523,587,523};  
 
    unsigned DELAY[] = {375,125,500,500,500,1000,  
              375,125,500,500,500,1000,  
              375,125,500,500,500,500,1000,  
              375,125,500,500,500,1000};  
    int i;  
    for (i = 0; i < 25; i++)  
    {  
              Beep(FREQUENCY[i], DELAY[i]);  
    }  
	*/
	mciSendString("open BGM//—@†D¤¯.mp3 alias bgm",NULL,"repeat",NULL);
	mciSendString("play bgm",NULL,0,NULL);
	//PlaySound("BGM//ClariS - —@†D¤¯.wav", 0, SND_ASYNC);
}
void Music_Choose()
{
	PlaySound("BGM//choose.wav", 0, SND_ASYNC);
}
void Music_Confirm()
{
	PlaySound("BGM//confirm.wav", 0, SND_ASYNC);
}
void Music_Lose()
{
	PlaySound("BGM//lose.wav", 0, SND_ASYNC);
}
void Music_Win()
{
	PlaySound("BGM//win.wav", 0, SND_ASYNC);
}