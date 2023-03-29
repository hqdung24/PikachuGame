#pragma once
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <vector>


#define VerticalDash 179;
#define HorizontalDash 196;
#define downleftcorn 192; 
#define uprightcorn 191; 
#define upleftcorn 218; 
#define downrightcorn 217; 

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

using namespace std;


void gotoxy(int x, int y);

void SetWindowSize(SHORT width, SHORT height);

void SetScreenBufferSize(SHORT width, SHORT height);

void DisableResizeWindow();

void ShowScrollbar(BOOL Show);

void ShowCur(bool CursorVisibility);

void DisableSelection();

void ConsoleSetting();

void setAndCenterWindow();

void playSound(int); //choose id of sound effect list, return 1 if succesfully play the sound
