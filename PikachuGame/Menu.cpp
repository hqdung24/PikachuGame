#pragma once

#include "Menu.h"
#include "Console.h"
string MenuList[10]{ "     START   ", " RULES OF GAME ", "  LEADERBOARD  ", "     QUIT     "};

void printBanner()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    gotoxy(0, 10);
    cout << R"( 
                                  ______   _____  _    _           ______  _     _  _     _ 
                                 (_____ \ (_   _)| |  / )   /\    / _____)| |   | || |   | |
                                  _____) )  | |  | | / /   /  \  | /      | |__ | || |   | |
                                 |  ____/   | |  | |< <   / /\ \ | |      |  __)| || |   | |
                                 | |       _| |_ | | \ \ | |--| || \_____ | |   | || |___| |
                                 |_|      (_____)|_|  \_)|_|  |_| \______)|_|   |_| \______|
                                   
)";
    cout << right << setw(77) << "by: huyndungg && hoangkhangg ";
}

void drawBackground(int x, int y)
{
    gotoxy(x, y-1);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout << R"(   
                                                                                     _.--""`-..
                                                                                    ,'          `.
                                                                                  ,'          __  `.
                                                                                 /|          " __   \
                                                                                , |           / |.   .
                                                                                |,'          !_.'|   |
                                                                              ,'             '   |   |
                                                                             /              |`--'|   |
                                                                            |                `---'   |
                                                                             .   ,                   |                       ,".
                                                                              ._     '           _'  |                    , ' \ `
                                                                          `.. `.`-...___,...---""    |       __,.        ,`"   L,|
                                                                          |, `- .`._        _,-,.'   .  __.-'-. /        .   ,    \
                                                                        -:..     `. `-..--_.,.<       `"      / `.        `-/ |   .
                                                                          `,         """"'     `.              ,'         |   |  ',,
                                                                            `.      '            '            /          '    |'. |/
                                                                              `.   |              \       _,-'           |       ''
                                                                                `._'               \   '"\                .      |
                                                                                   |                '     \                `._  ,'
                                                                                   |                 '     \                 .'|
                                                                                   |                 .      \                | |
                                                                                   |                 |       L              ,' |
                                                                                   `                 |       |             /   '
                                                                                    \                |       |           ,'   /
                                                                                  ,' \               |  _.._ ,-..___,..-'    ,'
                                                                                 /     .             .      `!             ,j'
                                                                                /       `.          /        .           .'/
                                                                               .          `.       /         |        _.'.'
                                                                                `.          7`'---'          |------"'_.'
                                                                               _,.`,_     _'                ,''-----"'
                                                                           _,-_    '       `.     .'      ,\
                                                                           -" /`.         _,'     | _  _  _.|
                                                                            ""--'---"""""'        `' '! |! /
                                                                                                    `" " -'
                                
)";
    gotoxy(x, y-1);
    SetConsoleTextAttribute(hConsole, 14);
    cout << R"(                
                                            ,-.
                                          _.|  '
                                        .'  | /
                                      ,'    |'
                                     /      /
                       _..----""---.'      /
 _.....---------...,-""                  ,'
 `-._  \                                /
     `-.+_            __           ,--. .
          `-.._     .:  ).        (`--"| \
               7    | `" |         `...'  \
               |     `--'     '+"        ,". ,""-
               |   _...        .____     | |/    '
          _.   |  .    `.  '--"   /      `./     j
         \' `-.|  '     |   `.   /        /     /
         '     `-. `---"      `-"        /     /
          \       `.                  _,'     /
           \        `                        .
            \                                j
             \                              /
              `.                           .
                +                          \
                |                           L
                |                           |
                |  _ /,                     |
                | | L)'..                   |
                | .    | `                  |
                '  \'   L                   '
                 \  \   |                  j
                  `. `__'                 /
                _,.--.---........__      /
               ---.,'---`         |   -j"
                .-'  '....__      L    |
          )";
}


void choosePointer(int x, int y, int choosing)
{
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14*choosing);
    gotoxy(x-2, y );
    cout << ">>" ;
    gotoxy(x+19, y);
    cout << "<<";
}

void printMainMenu(int x, int y, int cursor)
{
   
    int i = 0;
    int color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
    while (i<4) {
        gotoxy(x, y);
        if (i == cursor)
        {//highlight background

            drawRectangle(x+1, y + i * 3, 17, 3, 0);
            color = 14;
            drawRectangle(x, y + i * 3, 19, 3, color);
            printText(MenuList[i], x+2, y + i * 3 + 1, color);
            choosePointer(x,y + i * 3+1, 1);
        }
        else
        {
            drawRectangle(x, y + i * 3, 19, 3, 0);
            color = 11;
            drawRectangle(x+1 ,y + i * 3, 17, 3, color);
            printText(MenuList[i], x+2, y + i * 3 + 1, color);
            choosePointer(x, y + i * 3 + 1, 0);
        }
        i++;
    }
   
}

int MenuChoice() //MOVE UP AND DOWN, RETURN THE CHOICE
{
    char ch;
    
    int cursor = 0;

    int choice = 0;
    drawBackground(0, 20);
    printMainMenu(52, 20, cursor);
    while (true) 
    {
        ch = _getch();
        if (ch == 72 && cursor != 0) 
        { // up arrow
            playSound(1, 1);
            cursor--;
        }
        else if (ch == 80 && cursor < 4 - 1) 
        { // down arrow
            playSound(1, 1);
            cursor++;
        }
        else if (ch == '\r')
        {//enter key
            playSound(2, 1);
            Sleep(300);
            return cursor;
        }
        printMainMenu(52, 20, cursor);
    }
}

void printText(const string text, int x, int y, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    gotoxy(x, y);
    cout << text;
}

void drawVerticalLine(int x, int y, int length, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < length; i++)
    {
        gotoxy(x, y + i);
        cout << (char)VerticalDash;
    }
}
void drawHorizontalLine(int x, int y, int length, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < length; i++)
    {
        gotoxy(x + i, y);
        cout << (char)HorizontalDash;
    }
}

void drawRectangle(int x, int y, int width, int length, int color)
{
  
    //gotoxy(x + j, y + i);
    drawHorizontalLine(x, y + 0, width, color);
    drawHorizontalLine(x, y + length - 1, width, color);

    //gotoxy(x + j, y + i);
    drawVerticalLine(x + 0, y, length, color);
    drawVerticalLine(x + width - 1, y, length, color);

    gotoxy(x, y); cout << (char)upleftcorn;
    gotoxy(x + width - 1, y); cout << (char)uprightcorn;
    gotoxy(x + width - 1, y + length - 1); cout << (char)downrightcorn;
    gotoxy(x, y + length - 1); cout << (char)downleftcorn;
}

void printLeaderBoard()
{
    system("CLS");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, LIGHT_RED);
    gotoxy(5, 5);
    cout << R"(
                              _                      _               ___                         _ 
                             | |     ___   __ _   __| |  ___   _ _  | _ )  ___   __ _   _ _   __| |
                             | |__  / -_) / _` | / _` | / -_) | '_| | _ \ / _ \ / _` | | '_| / _` |
                             |____| \___| \__,_| \__,_| \___| |_|   |___/ \___/ \__,_| |_|   \__,_|
                                                                                                   )";
    int id = 1;
    drawRectangle(34, 11, 60, 33, LIGHT_AQUA);
    for (int i = 1; i < 34; i++)
    {
        if (i == 2)
        {
            SetConsoleTextAttribute(hConsole, WHITE);
            gotoxy(35, 10 + i);
            cout << left<<setw(8) <<" RANK" <<setw(20)<< "USERNAME" <<setw(20)<< "RECORD " << "DATE";
        }
        else 
        {
            if (i % 2 == 0)
            {
                
                gotoxy(36, 10 + i);
                if (id <=3 && id >=1) SetConsoleTextAttribute(hConsole, RED);
                else if (id <=10) SetConsoleTextAttribute(hConsole, GREEN);
                else SetConsoleTextAttribute(hConsole, WHITE);
                cout << id++ << ".";
            }
            if (i % 2 != 0)
            {
                gotoxy(34, 10 + i);
                drawHorizontalLine(35, 10 + i, 58, LIGHT_AQUA);
            }
        }
    }
}



