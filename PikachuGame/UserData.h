#pragma once
#include "Menu.h"
#include <ctime>
#include <fstream>
void printInforBox(int x, int y);
int EnterInfor(Player playerlist[100], int& n, int x, int y); //n : number of players that played the game before
void stateSave(board a, COORD cursor, int columns, int rows, State& s);
void stateRead(board& a, COORD& cursor, int columns, int rows, State& s);
void binaryRead(Player player[], const char* fileName, int n);
void binaryWrite(Player player[], const char* fileName, int n);
void sortLeaderboard(Player p[], int amountPlayer);


