#pragma once
#include <iostream>
#include "Console.h"

using namespace std;

struct cell
{
    char box[5][10] = 
    {
            {" ------- "},
            {"|       |"},
            {"|       |"},
            {"|       |"},
            {" ------- "}
    };
    char key = '0';
    bool isSelected = 0;
};


struct Date
{
    int dd, mm, yy;
};

struct Record
{
    Date date;
    int points;
};

struct player
{
    string name;
    Record rc;
};


