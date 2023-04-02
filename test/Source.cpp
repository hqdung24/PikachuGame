#include <iostream>
#include <queue>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <vector>
#include <mmsystem.h>
#include <conio.h>
using namespace std;
struct test
{
    int fisrt;
    int secord;
};
#define VerticalDash 179;
#define HorizontalDash 196;
#define downleftcorn 192; 
#define uprightcorn 191; 
#define upleftcorn 218; 
#define downrightcorn 217; 
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
struct point
{
    int x;
    int y;
};

void printArray(int a[6][6], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << a[i][k] << " ";
        }
        cout << endl;
    }
}


void generateRandomMatrix(int curboard[8][8], int ROWS, int COLS, int amountpoke)
{
    int* typeLimit = new int[8];
    //min xài để đếm số lượng tối thiểu 1 pokemon sẽ xuất hiện
    int minPoke = (ROWS * COLS) / amountpoke;
    //excess dùng để tính có bao nhiêu pokemon sẽ dc +2 vào số lượng có thể dc xuất hiện
    int excessPoke = ((ROWS * COLS) % amountpoke) / 2;
    //phân bổ số lượng vào từng pokemon
    for (int i = 0; i < amountpoke; i++)
    {
        typeLimit[i] = minPoke;
    }
    //chọn ngẫu nhiên những pokemon dc xuất hiện nhiều hơn 
    for (int i = 0; i < excessPoke; i++)
    {
        typeLimit[rand() % amountpoke] += 2;
    }

    int type[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int countType[8] = { 0, 0, 0, 0, 0, 0, 0,0 };
    //khai báo mảng động

    //Tạo phần tử ngẫu nhiên
    for (int i = 1; i < ROWS - 1 ; i++) {
        for (int k = 1; k < COLS - 1 ; k++)
        {
            int random;
            do {
                random = rand() % 8;
            } while (countType[random] >= typeLimit[random]);
            curboard[i][k] = (char)(0 + type[random]);
            countType[random]++;
        }

    }
}

void coutMatrix(int game[8][8], int n)
{
    for (int i = 0; i < n ; i++)
    {
        cout << "  ";
        for (int k = 0; k < n ; k++)
        {
            cout << game[i][k] << "  ";
        }
        cout << endl;
    }
}

void getNeighbours(vector<COORD> &neighbours, COORD node, int board[8][8])
{
   
    COORD nxy[4] = { -1, 0, 1, 0, 0 , 1, 0, -1 };
    neighbours.clear();
    for (int i = 0; i < 4; i++)
    {
        COORD p;
        if (board[node.Y + nxy[i].Y][node.X + nxy[i].X] != 3 )
        {
            p.Y = node.Y + nxy[i].Y;
            p.X = node.X + nxy[i].X;
        }
        neighbours.push_back(p);
    }
}


void clearQueue(queue <int> &q)
{
    // I want to avoid pop in a loop
    while (!q.empty())
    {
        q.pop();
    }
}

COORD intToCOORD(int P, int ROWS, int COLS)
{
    COORD result;
    result.Y = (P % 8 == 0) ? P/8-1 : (P / 8 );
    result.X = (P % 8 == 0) ? 7 : (P % 8 - 1);
    return result;
}

int COORDToint(COORD p, int ROWS, int COLS)
{
    return (p.Y) * COLS + p.X + 1;
}

int* solveBFS(COORD s, COORD e, int board[8][8], int ROWS, int COLS) //s : start cell, e : end cell
{
    //xét mảng 2 chiều như mảng 1 chiều
    int Xs = COORDToint(s, ROWS, COLS);
    int Xe = COORDToint(s, ROWS, COLS);

    queue<int> q;
    vector<COORD> neighbours;
    int* prev = new int[100] {0};
    int node{NULL};
    bool visited[64]{false};


    q.push(Xs); //enqueue
    visited[Xs] = true;
    

    while (!q.empty())
    {
        node = q.front();
        getNeighbours(neighbours, intToCOORD(node, ROWS, COLS), board);
        q.pop(); 

        //return the first element of the queue and dequeue


        for (COORD next : neighbours)
        {
            if (!visited[COORDToint(next, ROWS, COLS)])
            {
                q.push(COORDToint(next, ROWS, COLS));
                visited[COORDToint(next, ROWS, COLS)] = true;
                prev[COORDToint(next, ROWS, COLS)] = node;
                COORDToint(next, ROWS, COLS);
            }
        }
    }
    return prev;
}

vector<int> drawPath(COORD s, COORD e, int board[8][8], int ROWS, int COLS)
{
    int* prev = solveBFS(s, e, board, 8, 8);
    vector<int> path{NULL};
    for (int at = COORDToint(e,ROWS, COLS); at != NULL; at = prev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
void gotoxy(int x, int y)// di chuyen con tro tren console de thuc hien cau lenh in
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(hConsole, cord);
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
    
    for (int i = 0; i < length; i++)
    {
        gotoxy(x, y+i);
        cout << (char)VerticalDash;
    }
}
void drawHorizontalLine(int x, int y, int length, int color)
{
    
    for (int i = 0; i < length; i++)
    {
        gotoxy(x+i, y);
        cout << (char)HorizontalDash;
    }
}

void drawRectangle(int x, int y, int width, int length, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
       
    //gotoxy(x + j, y + i);
    drawHorizontalLine(x , y + 0, width , color);
    drawHorizontalLine(x , y + length - 1, width , color);
                
    //gotoxy(x + j, y + i);
    drawVerticalLine(x + 0, y , length, color);
    drawVerticalLine(x + width - 1, y , length, color);
            
    gotoxy(x, y); cout << (char)upleftcorn;
    gotoxy(x + width - 1, y); cout << (char)uprightcorn;
    gotoxy(x + width - 1, y + length - 1); cout << (char)downrightcorn;
    gotoxy(x, y + length - 1); cout << (char)downleftcorn;
    SetConsoleTextAttribute(hConsole, 7);
}

void drawSubTable(int x, int y, int width, int length)
{
    //SCORE table
    drawRectangle(x - 5 , y  , width + 10, length * 3 + 5, rand()%15+1);
    drawRectangle(x, y + 1, width, length , WHITE);
    printText("SCORE : ", x + 3, y + 2, RED);
    y +=  1 + length; //draw table vertically    
   
    drawRectangle(x - 4, y, width + 8, length*3, WHITE);
    y++;
    printText(" <SHORTCUTS>", x + 3 , y++, LIGHT_RED);
    printText("S : SURRENDER", x - 2, y ++, LIGHT_GREEN);
    printText("H : GET A MOVE SUGGESTION", x - 2 , y ++, LIGHT_AQUA);
    printText("L : VIEW LEADERBOARD", x - 2  , y ++, LIGHT_YELLOW);
    printText("M : TURN OFF MUSIC", x - 2  , y ++, LIGHT_PURPLE);
    printText("R : READ RULE OF GAME", x - 2  , y ++, YELLOW);
}

//0, 0, 0, 0, 0, 0, 0, 0
//0, 1, 2, 0, 1, 2, 1, 0
//0, 2, 1, 0, 1, 2, 1, 0
//0, 2, 1, 0, 1, 2, 1, 0
//0, 1, 2, 1, 2, 1, 1, 0
//0, 1, 2, 1, 2, 1, 1, 0
//0, 0, 1, 0, 2, 1, 2, 0
void swap(test& a, test& b)
{
    test t = a;
    a = b;
    b = t;
}
void drawBox(char cell[5][10], int row, int col) //row, col of the board
{
    for (int i = 0; i < 5; i++)
    {
        gotoxy(col * 10, row * 5 + i); // X LA COT, Y LA HANG
        cout << cell[i] << endl;
    }
}
void drawdeBox(char cell[5][10], int row, int col) //row, col of the board
{
    for (int i = 0; i < 5; i++)
    {
        // X LA COT, Y LA HANG
        for (int j = 0; j < 10; j++)
        {
            gotoxy(col * 10, row * 5 + i);
            cout << "\b";
        }
        cout << endl;
    }
}
void ShowCur(bool CursorVisibility)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = false; // set the cursor visibility to false
    SetConsoleCursorInfo(consoleHandle, &info);
}
int main()
{
    char box[5][10] =
    {
            {" ------- "},
            {"|       |"},
            {"|   0   |"},
            {"|       |"},
            {" ------- "}
    };
  
 
   /* coutMatrix(curboard, 8);
       int* path = new int[100];
    COORD s = { 1, 1 };
    COORD e = { 4, 1 };
    path = solveBFS(s, e, curboard, 8, 8);
    for (int i = 0; i < 100; i++)
        cout << path[i];*/
    /*drawSubTable(10, 5, 20, 3);
    
    cout << endl;
    char c;
    cin >> c;*/
    test a{1, 1};
    test b{ 2, 2 };
    cout << a.fisrt << a.secord << endl;
    cout << b.fisrt << b.secord;
    swap(a, b);
    cout << a.fisrt << a.secord << endl;
    cout << b.fisrt << b.secord;
}
