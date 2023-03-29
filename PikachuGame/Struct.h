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
            {"|   0   |"},
            {"|       |"},
            {" ------- "}
    };
    char key = '0';
    bool isSelected = 0;

    void renderbox()
    {
       /* box[0][0] = '\u2514';
        box[4][9] = (char)lowrightcorn;
        box[0][9] = (char)uprightcorn;
        box[4][0] = (char)lowleftcorn;*/
        for (int i = 1; i < 8; i++)
        {
            box[0][i] = (char)196;
        }
        for (int i = 1; i < 8; i++)
        {
            box[4][i] = (char)196;
        }

        for (int i = 1; i < 4; i++)
        {
            box[i][0] = (char)179;
        }
        for (int i = 1; i < 4; i++)
        {
            box[i][8] = (char)179;
        }
        box[0][0] = (char)upleftcorn;
        box[4][0] = (char)downleftcorn;
        box[4][8] = (char)downrightcorn
        box[0][8] = (char)uprightcorn;
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
    string id;
    Record rc;
};


