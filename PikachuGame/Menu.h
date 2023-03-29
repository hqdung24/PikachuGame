#pragma once
#include <iostream>
#include <conio.h> // for getch() function
#include <windows.h>
#include <time.h>
#include <iomanip>

using namespace std; 
void printBanner();
void printMainMenu(int x, int y, int cursor);
void printLeaderBoard();
int MenuChoice();
void drawBackground(int x, int y);

void printText(const string text, int x, int y, int color);
void drawVerticalLine(int x, int y, int length, int color);
void drawHorizontalLine(int x, int y, int length, int color);
void drawRectangle(int x, int y, int width, int length, int color);

