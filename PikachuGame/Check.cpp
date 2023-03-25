#include "Check.h"

int checkX(board a, int y1, int y2, int x)
{
    if (y1 == y2)
        return 0;
    int maxP = max(y1, y2);
    int minP = min(y1, y2);
    // cho y chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[x][i].KeyinBox() != '0')
            return 0;
    }
    // return 1 khi đã kiểm tra đường dọc hợp lệ
    return 1;
}

int checkY(board a, int x1, int x2, int y)
{
    if (x1 == x2)
        return 0;
    int maxP = max(x1, x2);
    int minP = min(x1, x2);
    // cho x chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[i][y].KeyinBox() != '0')
            return 0;
    }
    // return 1 khi đã kiểm tra đường ngang hợp lệ
    return 1;
}



int checkZ(board a, COORD p1, COORD p2)
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

int checkL(board a, COORD p1, COORD p2)
{
    if (checkY(a, p1.Y, p2.Y, max(p1.X, p2.X)) && checkX(a, p1.X, p2.X, max(p1.Y, p2.Y)))
        return 1;
    if (checkY(a, p1.Y, p2.Y, min(p1.X, p2.X)) && checkX(a, p1.X, p2.X, min(p1.Y, p2.Y)))
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
    // kt bên trái
    for (int i = minX; i >= 0; i--)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkY(a, minY - 1, maxY + 1, i) == 1)
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkX(a, p1.X, i, p1.Y) == 1 && checkX(a, p2.X, i, p2.Y == 1))
                return 1;
        }
    }
    // kt bên dưới
    for (int i = maxY; i < boardSize; i++)
    {
        if (checkX(a, minX - 1, maxX + 1, i) == 1)
        {
            if (checkY(a, p1.Y, i, p1.X) == 1 && checkX(a, p2.Y, i, p2.X) == 1)
                return 1;
        }
    }
    // kt bên trên
    for (int i = maxY; i < boardSize; i++)
    {
        if (checkX(a, minX - 1, maxX + 1, i) == 1)
        {
            if (checkY(a, p1.Y, i, p1.X) == 1 && checkX(a, p2.Y, i, p2.X) == 1)
                return 1;
        }
    }
    return 0;
}

bool checkAll(board a, COORD p1, COORD p2, int boardSize) 
{
    return (checkX(a, p1.Y, p2.Y, p1.X) || checkY(a, p1.X, p2.X, p1.Y) || checkL(a, p1, p2) 
        || checkZ(a, p1, p2) || checkU(a, p1, p2, boardSize));

}