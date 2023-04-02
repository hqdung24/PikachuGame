#pragma once
#include <iostream>
#include <conio.h> // for getch() function
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <mmsystem.h>
#include <string>
#include <vector>
#include <wincon.h>
#include "Struct.h"
#include "UserData.h"
using namespace std;
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


void printBanner(string username);
void printMenu(string menuType[], int size, int x, int y, int cursor);
void printLeaderBoard();
int MainMenuChoice();
void drawBackground(int x, int y);
void printText(const string text, int x, int y, int color);
void drawVerticalLine(int x, int y, int length, int color);
void drawHorizontalLine(int x, int y, int length, int color);
void drawRectangle(int x, int y, int width, int length, int color);
int StartMenuChoice(Player playerlist[100], int& n);
void game(Player playerlist[10], int n, int index);
