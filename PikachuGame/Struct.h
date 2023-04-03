
#pragma once

#include "Console.h"
#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100
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
typedef cell** board;

struct State { //Representing a board state
    int p, q; // Size of the board game
    int p_, q_; // Current cursor position
    char board[BOARDSIZE]; // Current board state
    int CurrentScore = 0;
};

struct Date
{
    int dd = 2;
    int mm = 4;
    int yy = 2023;
};

struct Record
{
    Date date;
    int points = 0;
};

struct Player
{
    char name[100];
    char password[100];
    Record record;
    State state[2]{ NULL, NULL };
    void recordSave(int score)
    {
        //ref: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
        time_t now = time(0);
        //phải xài biến now vì func localtime yêu cầu 1 con trỏ
        tm* ltm = localtime(&now);

        //gán giá trị
        //tm_year, tm_month, tm_day là biến con của struct tm *localtime(const time_t *time);
        record.date.yy = 1900 + ltm->tm_year; // +1900 vì tm_year cho biết đã bao nhiêu năm từ 1900
        record.date.mm = 1 + ltm->tm_mon; // +1 bởi vì tm_mon cho biết tháng của năm chạy từ 0 đến 11
        record.date.dd = ltm->tm_mday;
        record.points = score;
    }
    void outputDate()
    {
        string ngay = ((record.date.dd < 9) ? "0" + to_string(record.date.dd) : to_string(record.date.dd)) + "/" + ((record.date.mm < 12) ? "0" + to_string(record.date.mm) : to_string(record.date.mm)) + "/" + to_string(record.date.yy);
        cout << ngay;
    }
};




