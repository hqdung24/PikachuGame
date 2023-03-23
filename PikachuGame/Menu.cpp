#pragma once

#include "Menu.h"
#include "Console.h"
string MenuList[10]{ "|    START    |", "|   ACCOUNT   |", "| LEADERBOARD |", "|    QUIT     |"};

void printBanner()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    cout << R"( 
                      ______   _____  _    _           ______  _     _  _     _ 
                     (_____ \ (_   _)| |  / )   /\    / _____)| |   | || |   | |
                      _____) )  | |  | | / /   /  \  | /      | |__ | || |   | |
                     |  ____/   | |  | |< <   / /\ \ | |      |  __)| || |   | |
                     | |       _| |_ | | \ \ | |--| || \_____ | |   | || |___| |
                     |_|      (_____)|_|  \_)|_|  |_| \______)|_|   |_| \______|
                                                             )";
}

void printMenu(int x, int y, int cursor)
{
    gotoxy(x, y);
    int i = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    while (i<4) {
        if (i == cursor) //highlight background
        {
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED);
            cout  << "---------------" << endl;
            SetConsoleTextAttribute(hConsole, 2);
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED);
            cout << MenuList[i++] << endl;
            SetConsoleTextAttribute(hConsole, 2);
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED);
            cout  << "---------------" << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 10);
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, 10);
            cout << "---------------" << endl;

            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, 10);
            cout << MenuList[i++] << endl;

            SetConsoleTextAttribute(hConsole, 10);
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, 10);
            cout << "---------------" << endl;
        }
    }
}

int MenuChoice() //MOVE UP AND DOWN, RETURN THE CHOICE
{
    char ch;
    
    int cursor = -1;

    int choice = -1;

    printMenu(0, 10, cursor);
    while (true) 
    {
        ch = _getch();
        if (ch == 72 && cursor != 0) 
        { // up arrow
            cursor--;
        }
        else if (ch == 80 && cursor < 4 - 1) 
        { // down arrow
            cursor++;
        }
        else if (ch == '\r')
        {//enter key
            return cursor;
        }
        printMenu(0, 10, cursor);
    }
}






