#pragma once
#include"Check.h"
#include "Console.h"
#include"Menu.h"


board initialBoard(int ROWS, int COLS);

void getPosition(char input, COORD& CurPos, int ROWS, int COLS);
int selectCell(char input, COORD CurPos, board playingBoard);

void drawBox(char cell[5][10], int ROWS, int COLS);
void drawTable(COORD cursor, COORD helpp[2], board curboard, string background[], int ROWS, int COLS);
void releaseBoard(board board, int ROWS, int COLS);
void generateBoard(board& curboard, int ROWS, int COLS, int amountpoke);
void gameBackground(string background[], int boardsize);

void StandardMode1(Player& curplayer, int ROWS, int COLS, int Continue);
void drawSubTable(int x, int y, int width, int length, int score);





