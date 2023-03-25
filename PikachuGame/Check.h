#pragma once
#include <iostream>
#include "Struct.h"
#include <wincon.h>
#include <conio.h>

typedef cell** board;
using namespace std;

struct point
{
    int x;
    int y;
};

void printArray(int a[6][6], int n);
int checkX(board a, int y1, int y2, int x);
int checkY(board a, int x1, int x2, int y);


int checkZ(board a, COORD p1, COORD p2);
int checkL(board a, COORD p1, COORD p2);
int checkU(board a, COORD p1, COORD p2, int boardSize);
bool checkAll(board a, COORD p1, COORD p2, int boardSize);