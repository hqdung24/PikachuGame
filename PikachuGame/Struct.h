#pragma once
#include <iostream>
#include "Console.h"

using namespace std;

#define ldash 151;
#define lowleftcorn 192; 
#define uprightcorn 191; 
#define upleftcorn 217; 
#define lowrightcorn 192; 

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

    void ldashchange()
    {
       /* box[0][0] = '\u2514';
        box[4][9] = (char)lowrightcorn;
        box[0][9] = (char)uprightcorn;
        box[4][0] = (char)lowleftcorn;*/
        for (int i = 1; i < 8; i++)
        {
            box[0][i] = (char)ldash;
        }
        for (int i = 1; i < 8; i++)
        {
            box[4][i] = (char)ldash;
        }
    }

    void deBox()
    {
        key = '0';
        box[2][4] = key;
        isSelected = not isSelected;
    }

    int select()
    {
        isSelected = not isSelected;
        if (isSelected == 1) return 1;
        return -1;
    }
    char KeyinBox()
    {
       return box[2][4];
    }
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


