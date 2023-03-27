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

int checkX(board a, int y1, int y2, int x1, int x2);
int checkY(board a, int x1, int x2, int y1, int y2);


int checkZ(board a, COORD p1, COORD p2);
int checkL(board a, COORD p1, COORD p2);
int checkU(board a, COORD p1, COORD p2, int boardSize);
bool checkAll(board a, COORD p1, COORD p2, int boardSize);

bool helpFunc(board a, int boardSize, COORD& p1, COORD& p2);