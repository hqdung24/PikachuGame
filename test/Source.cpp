#include <iostream>
using namespace std;
#include <algorithm>
#include <Windows.h>
#include <string>
#include <vector>
#include <mmsystem.h>
string ct;

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

int checkX(int a[6][6], int y1, int y2, int X)
{
    int maxP = max(y1, y2);
    int minP = min(y1, y2);
    // cho y chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP; i < maxP; i++)
    {
        if (a[X][i] != 0)
            return 0;
    }
    // return 1 khi đã kiểm tra đường dọc hợp lệ
    return 1;
}

int checkY(int a[6][6], int x1, int x2, int y)
{
    int maxP = max(x1, x2);
    int minP = min(x1, x2);
    // cho x chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[i][y] != 0)
            return 0;
    }
    // return 1 khi đã kiểm tra đường ngang hợp lệ
    return 1;
}

int checkZ(int a[6][6], COORD p1, COORD p2)
{
    int maxX = max(p1.X, p2.X);
    int minX = min(p1.X, p2.X);
    int maxY = max(p1.Y, p2.Y);
    int minY = min(p1.Y, p2.Y);

    for (int i = minX; i < maxX; i++)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkY(a, minY - 1, maxY + 1, i) == 1)
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkX(a, p1.X, i, p1.Y) == 1 && checkX(a, p2.X, i, p2.Y) == 1)
                return 1;
        }
    }

    for (int i = minY; i < maxY; i++)
    {
        // tìm xem có cột hàng ngang nào trống ko
        if (checkY(a, minX - 1, maxX + 1, i) == 1)
        {
            // kt xem hàng dọc của từng vị trí có trống ko
            if (checkX(a, p1.Y, i, p1.X) == 1 && checkX(a, p2.Y, i, p2.X) == 1)
                return 1;
        }
    }

    return 0;
}

int checkL(int a[6][6], COORD p1, COORD p2)
{
    if (checkX(a, p1.Y, p2.Y, max(p1.X, p2.X)) && checkY(a, p1.X, p2.X, max(p1.Y, p2.Y)))
        return 1;
    if (checkX(a, p1.Y, p2.Y, min(p1.X, p2.X)) && checkY(a, p1.X, p2.X, min(p1.Y, p2.Y)))
        return 1;
    return 0;
}

int checkU(int a[6][6], COORD p1, COORD p2, int boardSize)
{
    int maxX = max(p1.X, p2.X);
    int minX = min(p1.X, p2.X);
    int maxY = max(p1.Y, p2.Y);
    int minY = min(p1.Y, p2.Y);
    // kt bên phải
    for (int i = maxX; i < boardSize; i++)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkY(a, minY - 1, maxY + 1, i) == 1)
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkX(a, p1.X, i, p1.Y) == 1 && checkX(a, p2.X, i, p2.Y) == 1)
                return 1;
        }
    }
    if (checkX(a, p1.X, boardSize - 1, p1.Y) == 1 && checkX(a, p2.X, boardSize - 1, p2.Y) == 1)
        return 1;
    // kt bên trái
    for (int i = minX; i >= 0; i--)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkY(a, minY - 1, maxY + 1, i) == 1)
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkX(a, p1.X, i, p1.Y) == 1 && checkX(a, p2.X, i, p2.Y) == 1)
                return 1;
        }
    }
    if (checkX(a, p1.X, 0, p1.Y) == 1 && checkX(a, p2.X, 0, p2.Y) == 1)
        return 1;
    // kt bên dưới
    for (int i = maxY; i < boardSize; i++)
    {
        if (checkX(a, minX - 1, maxX + 1, i) == 1)
        {
            if (checkY(a, p1.Y, i, p1.X) == 1 && checkX(a, p2.Y, i, p2.X) == 1)
                return 1;
        }
    }
    if (checkY(a, p1.Y, boardSize - 1, p1.X) == 1 && checkX(a, p2.Y, boardSize - 1, p2.X) == 1)
        return 1;
    // kt bên trên
    for (int i = maxY; i < boardSize; i++)
    {
        if (checkX(a, minX - 1, maxX + 1, i) == 1)
        {
            if (checkY(a, p1.Y, i, p1.X) == 1 && checkX(a, p2.Y, i, p2.X) == 1)
                return 1;
        }
    }
    if (checkY(a, p1.Y, 0, p1.X) == 1 && checkX(a, p2.Y, 0, p2.X) == 1)
        return 1;
    return 0;
}
bool isValidMove(int a[6][6], COORD p1, COORD p2, int boardSize)
{
    return (checkX(a, p1.Y, p2.Y, p1.X) || checkY(a, p1.X, p2.X, p1.Y) || checkL(a, p1, p2) || checkZ(a, p1, p2) || checkU(a, p1, p2, boardSize));
}
bool helpFunc(int a[6][6], int boardSize, COORD& p1, COORD& p2)
{
    // tìm kiếm 1 ô giống nhau
    for (int i = 1; i < boardSize - 1; i++)
    {
        for (int k = 1; k < boardSize - 1; k++)
        {
            if (a[i][k] != 0)
            {
                for (int n = i; n < boardSize - 1; n++)
                {
                    for (int m = k; m < boardSize - 1; m++)
                    {
                        if (a[i][k] == a[n][m])
                        {
                            p1.X = i;
                            p1.Y = k;
                            p2.X = n;
                            p2.Y = m;
                            if (isValidMove(a, p1, p2, boardSize))
                            {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    p1.X = 0;
    p1.Y = 0;
    p2.X = 0;
    p2.Y = 0;
    return 0;
}

void generateRandomMatrix(int curboard[6][6], int ROWS, int COLS, int amountpoke)
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
    for (int i = 0; i < ROWS ; i++) {
        for (int k = 0; k < COLS ; k++)
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

void coutMatrix(int game[6][6], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << game[i][k] << "  ";
        }
        cout << endl;
    }
}

//0 - MenuMusic
//1 - move
//2 - Enter
//3 - ingame Music
//4 - cell running sound
//5 - success delete 2 cell
//6 - fail delete 2 cell
//7 - winning
void playSound(int i)
{
    static vector<const wchar_t*> soundFile{ L"MenuMusic", L"move.wav", L"EnterSound.wav", L"ingameBackground1.wav", L"createBoardSound.wav",  L"SuccessDelete2Cells.wav", L"FailDelete2Cells.wav", L"winningSound.wav" };
    PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}

int main()
{
    int input = 7;
    
   
        Sleep(100);
        playSound(input);
        while (true) cout << " ";
    return 0;
}
