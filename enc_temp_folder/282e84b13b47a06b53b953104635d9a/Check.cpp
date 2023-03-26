#include "Check.h"
//x đi dọc (chỉ số cột), y đi ngang(chỉ sớ hàng)
int checkX(board a, int y1, int y2, int x1, int x2) //kt hàng ngang
{
    if (y1 == y2 || x1 != x2)
        return 0;
    int maxP = max(y1, y2);
    int minP = min(y1, y2);
    if (minP + 1 == maxP) {
        cout << "| 1" << endl;
        return 1;
    }
       
    // cho y chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[i][x2].KeyinBox() != '0')
            return 0;
    }
    // return 1 khi đã kiểm tra đường dọc hợp lệ
    cout << "| 1" << endl;
    return 1;
}

int checkY(board a, int x1, int x2, int y1,int y2)
{
    if (x1 == x2 || y1 != y2)
        return 0;
    int maxP = max(x1, x2);
    int minP = min(x1, x2);
    if (minP + 1 == maxP) {
        cout << "| 1" << endl;
        return 1;
    }
    // cho x chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[y1][i].KeyinBox() != '0')
            return 0;
    }
    // return 1 khi đã kiểm tra đường ngang hợp lệ
    cout << "| 2" << endl;
    return 1;
}



int checkZ(board a, COORD p1, COORD p2)
{
    int maxX = max(p1.X, p2.X);
    int minX = min(p1.X, p2.X);
    int maxY = max(p1.Y, p2.Y);
    int minY = min(p1.Y, p2.Y);

    for (int i = minX + 1; i < maxX; i++)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkX(a, minY - 1, maxY + 1, i, i))
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y)) {
                cout << "| 3" << endl;
                return 1;
            }
                
        }
    }

    for (int i = minY + 1; i < maxY; i++)
    {
        // tìm xem có cột hàng ngang nào trống ko
        if (checkY(a, minX - 1, maxX + 1, i, i))
        {
            // kt xem hàng dọc của từng vị trí có trống ko
            if (checkX(a, p1.Y, i, p1.X, p1.X) && checkX(a, p2.Y, i, p2.X, p2.X)) {
                cout << "| 3" << endl;
                return 1;
            }
         
        }
    }

    return 0;
}

int checkL(board a, COORD p1, COORD p2)
{
    int maxX = max(p1.X, p2.X);
    int minX = min(p1.X, p2.X);
    int maxY = max(p1.Y, p2.Y);
    int minY = min(p1.Y, p2.Y);
    if (checkX(a, minY, maxY + 1, minX, minX) && checkY(a, minX - 1, maxX, maxY, maxY))
        return 1;
    if (checkX(a, minY, maxY + 1, maxX, maxX) && checkY(a, minX, maxX + 1, minY, minY))
        return 1;
    if (checkX(a, minY, maxY + 1, maxX, maxX) && checkY(a, minX, maxX + 1, maxY, maxY))
        return 1;
    return 0;
}

int checkU(board a, COORD p1, COORD p2, int boardSize)
{
    int maxX = max(p1.X, p2.X);
    int minX = min(p1.X, p2.X);
    int maxY = max(p1.Y, p2.Y);
    int minY = min(p1.Y, p2.Y);
    // kt bên phải
    for (int i = maxX + 1; i < boardSize; i++)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkX(a, minY - 1, maxY + 1, i, i))
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y)) {
                cout << "| 4" << endl;
                return 1;
            }
        }
    }
    // kt bên trái
    for (int i = minX - 1; i >= 0; i--)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkX(a, minY - 1, maxY + 1, i, i))
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y)) {
                cout << "| 4" << endl;
                return 1;
            }
                
        }
    }
    // kt bên dưới
    for (int i = maxY + 1; i < boardSize; i++)
    {
        if (checkY(a, minX - 1, maxX + 1, i, i))
        {
            if (checkX(a, p1.Y, i, p1.X, p1.X) && checkX(a, p2.Y, i, p2.X, p2.X)) {
                cout << "| 4" << endl;
                return 1;
            }
             
        }
    }
    // kt bên trên
    for (int i = minY - 1; i >= 0; i--)
    {
        if (checkY(a, minX - 1, maxX + 1, i, i))
        {
            if (checkX(a, p1.Y, i, p1.X, p1.X) == 1 && checkX(a, p2.Y, i, p2.X, p2.X)) {
                cout << "| 4" << endl;
                return 1;
            }
               
        }
    }
    return 0;
}

bool checkAll(board a, COORD p1, COORD p2, int boardSize) 
{
        return (checkX(a, p1.Y, p2.Y, p1.X, p2.X) || checkY(a, p1.X, p2.X, p1.Y, p2.Y) || checkL(a, p1, p2)
            || checkZ(a, p1, p2) || checkU(a, p1, p2, 8)); 
}