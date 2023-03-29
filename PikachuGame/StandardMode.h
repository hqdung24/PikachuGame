#pragma once
#include"Check.h"
#include "Console.h"
#include"Menu.h"
#include <mmsystem.h>
#include <ctime>
#include <iomanip>


board initialBoard(int ROWS, int COLS);

void getPosition(char input, COORD& CurPos, int ROWS, int COLS);
int selectCell(char input, COORD CurPos, board playingBoard);

void drawBox(char cell[5][10], int ROWS, int COLS);
void drawTable(COORD cursor, COORD helpfuncp[2], board curboard, int ROWS, int COLS);
void setMargin(board board, int ROWS, int COLS);
void releaseBoard(board board, int ROWS, int COLS);
void generateBoard(board& curboard, int ROWS, int COLS, int amountpoke);
void gameBackground(int x, int y);

void StandardMode1(int, int);
void drawSubTable(int x, int y, int width, int length, int score);





