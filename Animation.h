#ifndef __ANIMATION_H__
#define __ANIMATION_H__



#define DELAY_LINE 100
#define PATH_MAIN "Bitmap//Main.txt"
#define PATH_AUTHOR "Bitmap//ASCII-Author.txt"
#define PATH_LOGO "Bitmap//ASCII-welcome.txt"
#define PATH_LEVEL "Bitmap//Level.txt"
#define PATH_LOSE "Bitmap//ASCII-lose.txt"
#define PATH_WIN "Bitmap//ASCII-win.txt"
#define PATH_HELP "Bitmap//help.txt"
#define PATH_SIMPLE_1 "Bitmap//ASCII-simple-1.txt"
#define PATH_EXIT "Bitmap//ASCII-exit.txt"
void Ani_basic_print(char * addr,int delay);
void Ani_Logo();
void Ani_Author();
void Ani_Main();
void Ani_Level();
void Ani_Win();
void Ani_Lose();
void Ani_Exit();
void Ani_Help();
#endif