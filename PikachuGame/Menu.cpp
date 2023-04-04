#pragma once
#include "Menu.h"
#include "Console.h"
#include "StandardMode.h"
using namespace std;
string MainMenu[10]{ "     PLAY    ", " RULES OF GAME ", "  LEADERBOARD  ", "   SIGN OUT   "};
string StartMenu[2] = {"     START   ", "     QUIT      "};
string NewOrContinueMenu[3] = { "    New Game   ", "    Continue   ", "     Back    " };
string GameDifficultMenu[3] = { "     Easy    ", "    Normal   ", "     Back    " };
string EmptyMenu[4] = { "             ", "             ", "             ", "             " };
void printBanner(string username)
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
    
        SetConsoleTextAttribute(hConsole, LIGHT_RED);
        printText("User : " + username, 55, 18, LIGHT_RED);
    
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

void drawRectangle(int x, int y, int width, int length, int color)//width là độ dài theo chiều ngang, length là độ dài theo chiều dọc
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

void printMenu(string menuType[], int size, int x, int y, int cursor)
{
    int i = 0;
    int color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (i < size) {
        gotoxy(x, y);
        if (i == cursor)
        {//highlight background

            drawRectangle(x + 1, y + i * 3, 17, 3, 0);
            color = 14;
            drawRectangle(x, y + i * 3, 19, 3, color);
            printText(menuType[i], x + 2, y + i * 3 + 1, color);
            choosePointer(x, y + i * 3 + 1, 1);
        }
        else
        {
            drawRectangle(x, y + i * 3, 19, 3, 0);
            color = 11;
            drawRectangle(x + 1, y + i * 3, 17, 3, color);
            printText(menuType[i], x + 2, y + i * 3 + 1, color);
            choosePointer(x, y + i * 3 + 1, 0);
        }
        i++;
    }
}

void printEmptyMenu(int size, int x, int y, int cursor)
{
    int i = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (i < size) {
    gotoxy(x, y);
    drawRectangle(x, y + i * 3, 19, 3, 0);
    drawRectangle(x + 1, y + i * 3, 17, 3, 0);
    printText(MainMenu[i], x + 2, y + i * 3 + 1, 0);
    choosePointer(x, y + i * 3 + 1, 0);
    i++;
    }
}

void printLeaderBoard(Player playerlist[100], int n)
{
    system("CLS");
    sortLeaderboard(playerlist, n);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, LIGHT_RED);
    gotoxy(5, 2);
    cout << R"(
                              _                      _               ___                         _ 
                             | |     ___   __ _   __| |  ___   _ _  | _ )  ___   __ _   _ _   __| |
                             | |__  / -_) / _` | / _` | / -_) | '_| | _ \ / _ \ / _` | | '_| / _` |
                             |____| \___| \__,_| \__,_| \___| |_|   |___/ \___/ \__,_| |_|   \__,_|
                                                                                                   )";
    int id = 0;
    drawRectangle(34, 8, 60, 33, LIGHT_AQUA);
    for (int i = 1; i < 34; i++)
    {
        if (i == 2)
        {
            SetConsoleTextAttribute(hConsole, WHITE);
            gotoxy(35, 7 + i);
            cout << left<<setw(8) <<" RANK" <<setw(20)<< "USERNAME" <<setw(20)<< "RECORD " << "DATE";
        }
        else 
        {
            if (i % 2 == 0)
            {
                
                gotoxy(36, 7 + i);
                if (id <=2 && id >=0) SetConsoleTextAttribute(hConsole, RED); //top 3
                else if (id <=9) SetConsoleTextAttribute(hConsole, GREEN); // top 10
                else SetConsoleTextAttribute(hConsole, WHITE); // others
                if (playerlist[0].record.points != 0)
                {
                    cout << left << setw(8) << id + 1 << setw(20) << playerlist[id].name << setw(17) << playerlist[id].record.points; playerlist[id++].outputDate();
                }
            }
            if (i % 2 != 0)
            {
                gotoxy(34, 7 + i);
                drawHorizontalLine(35, 7 + i, 58, LIGHT_AQUA);
            }
        }
    }
    char c;
    c = _getch();
}

int MainMenuChoice() //MOVE UP AND DOWN, RETURN THE CHOICE
{
    char ch;

    int cursor = 0;

    int choice = 0;
    //drawBackground(0, 20);
    printMenu(MainMenu, 4, 52, 20, cursor);
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
        printMenu(MainMenu, 4, 52, 20, cursor);
    }
}

int StartMenuChoice(Player playerlist[100], int& n) //RETURN THE INDEX OF PLAYER
{
    char ch;
    int cursor = 0;
    int choice = 0;
    //drawBackground(0, 20);
    printMenu(StartMenu, 2, 52, 20, cursor);
    while (true)
    {
        ch = _getch();
        if (ch == 72 && cursor != 0)
        { // up arrow
            playSound(1, 1);
            cursor--;
        }
        else if (ch == 80 && cursor < 2)
        { // down arrow
            playSound(1, 1);
            cursor++;
        }
        else if (ch == '\r')
        {//enter key
            playSound(2, 1);
            Sleep(300);
            system("CLS");
            if (cursor == 0)
            {
                int index = EnterInfor(playerlist, n, 40, 20);
                return index; //return index of current player
            }
            else return -1; // out game

        }
        printMenu(StartMenu, 2, 52, 20, cursor);
    }
}

int DifficultMenuChoice() //MOVE UP AND DOWN, RETURN THE CHOICE
{
    char ch;

    int cursor = 0;

    int choice = 0;
    //drawBackground(0, 20);
    printEmptyMenu(4, 52, 20, cursor);
    printMenu(GameDifficultMenu, 3, 52, 20, cursor);
    while (true)
    {
        ch = _getch();
        if (ch == 72 && cursor != 0)
        { // up arrow
            playSound(1, 1);
            cursor--;
        }
        else if (ch == 80 && cursor < 2)
        { // down arrow
            playSound(1, 1);
            cursor++;
        }
        else if (ch == '\r')
        {//enter key
            playSound(2, 1);
            Sleep(300);
            if (cursor == 0) return 6;
            if (cursor == 1) return 8;
            if (cursor == 2) return -1; //back
        }
        printMenu(GameDifficultMenu, 3, 52, 20, cursor);
    }
}

int NewOrContinueChoice() //MOVE UP AND DOWN, RETURN THE CHOICE
{
    char ch;

    int cursor = 0;

    int choice = 0;
    //drawBackground(0, 20);
    printEmptyMenu(5, 52, 20, cursor);
    printMenu(NewOrContinueMenu, 3, 52, 20, cursor);
    while (true)
    {
        ch = _getch();
        if (ch == 72 && cursor != 0)
        { // up arrow
            playSound(1, 1);
            cursor--;
        }
        else if (ch == 80 && cursor < 3)
        { // down arrow
            playSound(1, 1);
            cursor++;
        }
        else if (ch == '\r')
        {//enter key
            playSound(2, 1);
            Sleep(300);
            if (cursor == 0) return 0; //new game
            if (cursor == 1) return 1; //continue
            if (cursor == 2) return -1; //back
        }
        printMenu(NewOrContinueMenu, 3, 52, 20, cursor);
    }
}



void game(Player playerlist[100], int n, int index)
{
    int menuchoice = -1;
    do
    {
        system("CLS");
        string s(playerlist[index].name);
        printBanner(s);
        menuchoice = MainMenuChoice();
        switch (menuchoice)
        {
        case 0:
        {
            int size = DifficultMenuChoice();
            if (size == -1) break;
            else
            {
                //CHỖ NÀY SẼ VIẾT HÀM CHECK XEM PLAYER ĐÓ ĐÃ CHƠI MÀN ĐÓ HAY CHƯA, NẾU CHƯA THÌ VÀO THẲNG GAME, NẾU RỒI THÌ GỌI HÀM NewOrContinueChoice();
                if (playerlist[index].state[(size == 6) ? 0 : 1].board[0] != '\0') //da choi truoc do
                {
                    int Continue = NewOrContinueChoice(); // chọn continue hay new game
                    if (Continue == -1) break;
                    playSound(0, -1);
                    StandardMode1(playerlist[index], size, size, Continue);
                }
                else // chua choi truoc do
                {
                    playSound(0, -1);
                    StandardMode1(playerlist[index], size, size, 0);
                }
                break;
            }
        }
        case 1:
        {
            system("ClS");
            break;
        }
        case 2:
        {
            printLeaderBoard(playerlist, n);
            break;
        }
        case 3: //Sign out option
        {
            cout << "3";
            binaryWrite(playerlist, "test.bin", n, 'k');
            break;
        }
        default:
        {
            menuchoice = -1;
            break;
        }
        }
    } while (menuchoice != 3);
}
