#include "Check.h"
#include "Menu.h"
// x đi dọc (chỉ số cột), y đi ngang(chỉ sớ hàng)
int checkX(board a, int y1, int y2, int x1, int x2) // kt hàng ngang
{
    if (y1 == y2 || x1 != x2)
        return 0;
    int maxP = max(y1, y2);
    int minP = min(y1, y2);
    if (minP + 1 == maxP)
        return 1;

    // cho y chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[i][x2].KeyinBox() != '0')
            return 0;
    }
    // return 1 khi đã kiểm tra đường dọc hợp lệ

    return 1;
}

int checkY(board a, int x1, int x2, int y1, int y2)
{
    if (x1 == x2 || y1 != y2)
        return 0;
    int maxP = max(x1, x2);
    int minP = min(x1, x2);
    if (minP + 1 == maxP)
        return 1;

    // cho x chạy đến khi nào gặp vật cản hoặc tịt đường
    // return 0 khi ko có đường đi
    for (int i = minP + 1; i < maxP; i++)
    {
        if (a[y1][i].KeyinBox() != '0')
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

    for (int i = minX + 1; i < maxX; i++)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkX(a, minY - 1, maxY + 1, i, i))
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y))
                return 3;
        }
    }

    for (int i = minY + 1; i < maxY; i++)
    {
        // tìm xem có cột hàng ngang nào trống ko
        if (checkY(a, minX - 1, maxX + 1, i, i))
        {
            // kt xem hàng dọc của từng vị trí có trống ko
            if (checkX(a, p1.Y, i, p1.X, p1.X) && checkX(a, p2.Y, i, p2.X, p2.X))
                return 3;
        }
    }

    return 0;
}

int checkL(board a, COORD p1, COORD p2)
{
    if (p1.Y > p2.Y)
    {
        if (p1.X > p2.X)
        {
            if (checkX(a, p2.Y - 1, p1.Y, p1.X, p1.X) && checkY(a, p2.X, p1.X + 1, p2.Y, p2.Y))
                return 2;
            if (checkX(a, p2.Y, p1.Y + 1, p2.X, p2.X) && checkY(a, p2.X - 1, p1.X, p1.Y, p1.Y))
                return 2;
        }
        if (p1.X < p2.X)
        {
            if (checkX(a, p2.Y - 1, p1.Y, p1.X, p1.X) && checkY(a, p1.X - 1, p2.X, p2.Y, p2.Y))
                return 2;
            if (checkX(a, p2.Y, p1.Y + 1, p2.X, p2.X) && checkY(a, p1.X, p2.X + 1, p1.Y, p1.Y))
                return 2;
        }
    }
    if (p1.Y < p2.Y)
    {
        if (p1.X > p2.X)
        {
            if (checkX(a, p1.Y, p2.Y + 1, p1.X, p1.X) && checkY(a, p2.X, p1.X + 1, p2.Y, p2.Y))
                return 2;
            if (checkX(a, p1.Y - 1, p2.Y, p2.X, p2.X) && checkY(a, p2.X - 1, p1.X, p1.Y, p1.Y))
                return 2;
        }
        if (p1.X < p2.X)
        {
            if (checkX(a, p1.Y, p2.Y + 1, p1.X, p1.X) && checkY(a, p1.X - 1, p2.X, p2.Y, p2.Y))
                return 2;
            if (checkX(a, p1.Y - 1, p2.Y, p2.X, p2.X) && checkY(a, p1.X, p2.X + 1, p1.Y, p1.Y))
                return 2;
        }
    }
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
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y))
                return 3;
        }
    }
    // kt bên trái
    for (int i = minX - 1; i >= 0; i--)
    {
        // tìm xem có cột hàng dọc nào trống ko
        if (checkX(a, minY - 1, maxY + 1, i, i))
        {
            // kt xem hàng ngang của từng vị trí có trống ko
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y))
                return 3;
        }
    }
    // kt bên dưới
    for (int i = maxY + 1; i < boardSize; i++)
    {
        if (checkY(a, minX - 1, maxX + 1, i, i))
        {
            if (checkX(a, p1.Y, i, p1.X, p1.X) && checkX(a, p2.Y, i, p2.X, p2.X))
                return 3;
        }
    }
    // kt bên trên
    for (int i = minY - 1; i >= 0; i--)
    {
        if (checkY(a, minX - 1, maxX + 1, i, i))
        {
            if (checkX(a, p1.Y, i, p1.X, p1.X) == 1 && checkX(a, p2.Y, i, p2.X, p2.X))
                return 3;
        }
    }
    return 0;
}

bool checkAll(board a, COORD p1, COORD p2, int boardSize)
{

    //drawVerticalLine(7 * 10 +3, 1 * 5, 5, color);
    //drawHorizontalLine(7 * 10, 2 * 5 + 2, 5, color);
    return (checkX(a, p1.Y, p2.Y, p1.X, p2.X) || checkY(a, p1.X, p2.X, p1.Y, p2.Y) || checkL(a, p1, p2) || checkZ(a, p1, p2) || checkU(a, p1, p2, 8));
}

// x đi dọc (chỉ số cột), y đi ngang(chỉ sớ hàng)
int checkXDraw(board a, int y1, int y2, int x1, int x2, int color) // kt hàng ngang
{
    if (y1 == y2 || x1 != x2)
        return 0;
    int maxP = max(y1, y2);
    int minP = min(y1, y2);
    if (minP + 1 == maxP) {
        drawVerticalLine(x1 * 10 + 4, minP * 5 + 3, abs(y1 - y2) * 5 - 1, color);
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
    drawVerticalLine(x1 * 10 + 4, minP * 5 + 3, abs(y1 - y2) * 5 - 1, color);
    return 1;
}

int checkYDraw(board a, int x1, int x2, int y1, int y2, int color)
{
    if (x1 == x2 || y1 != y2)
        return 0;
    int maxP = max(x1, x2);
    int minP = min(x1, x2);
    if (minP + 1 == maxP) {
        drawHorizontalLine(minP * 10 + 5, y1 * 5 + 2, abs(x1 - x2) * 10 - 1, color);
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
    drawHorizontalLine(minP * 10 + 5, y1 * 5 + 2, abs(x1 - x2) * 10 - 1, color);
    return 1;
}

int checkZDraw(board a, COORD p1, COORD p2, int color)
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
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y))
            {
                drawVerticalLine(i * 10 + 4, minY * 5 + 3, (maxY - minY) * 5 - 1, color);
                if ((p1.X < p2.X && p1.Y < p2.Y) || (p1.X > p2.X && p1.Y > p2.Y)) {
                    gotoxy(i * 10 + 4, minY * 5 + 2);
                    cout << (char)uprightcorn;
                    gotoxy(i * 10 + 4, maxY * 5 + 2);
                    cout << (char)downleftcorn;
                }
                else {
                    gotoxy(i * 10 + 4, minY * 5 + 2);
                    cout << (char)upleftcorn;
                    gotoxy(i * 10 + 4, maxY * 5 + 2);
                    cout << (char)downrightcorn;
                }

                drawHorizontalLine(min(p1.X, i) * 10 + 5, p1.Y * 5 + 2, abs(i - p1.X) * 10 - 1, color);
                drawHorizontalLine(min(p2.X, i) * 10 + 5, p2.Y * 5 + 2, abs(i - p2.X) * 10 - 1, color);
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
            if (checkX(a, p1.Y, i, p1.X, p1.X) && checkX(a, p2.Y, i, p2.X, p2.X))
            {
                drawHorizontalLine(minX * 10 + 5, i * 5 + 2, (maxX - minX) * 10 - 1, color);
                if ((p1.X < p2.X && p1.Y < p2.Y) || (p1.X > p2.X && p1.Y > p2.Y))
                {
                    gotoxy(minX * 10 + 4, i * 5 + 2);
                    cout << (char)downleftcorn;
                    gotoxy(maxX * 10 + 4, i * 5 + 2);
                    cout << (char)uprightcorn;
                }
                else {
                    gotoxy(minX * 10 + 4, i * 5 + 2);
                    cout << (char)upleftcorn;
                    gotoxy(maxX * 10 + 4, i * 5 + 2);
                    cout << (char)downrightcorn;
                }

                drawVerticalLine(p1.X * 10 + 4, min(p1.Y, i) * 5 + 3, abs(i - p1.Y) * 5 - 1, color);
                drawVerticalLine(p2.X * 10 + 4, min(p2.Y, i) * 5 + 3, abs(i - p2.Y) * 5 - 1, color);
                return 1;

            }
        }
    }

    return 0;
}

int checkLDraw(board a, COORD p1, COORD p2, int color)
{
    if (p1.Y > p2.Y)
    {
        if (p1.X > p2.X)
        {
            if (checkX(a, p2.Y - 1, p1.Y, p1.X, p1.X) && checkY(a, p2.X, p1.X + 1, p2.Y, p2.Y))
            {
                drawVerticalLine(p1.X * 10 + 4, p2.Y * 5 + 3, abs(p1.Y - p2.Y) * 5 - 1, color);
                gotoxy(p1.X * 10 + 4, p2.Y * 5 + 2);
                cout << (char)uprightcorn;
                drawHorizontalLine(p2.X * 10 + 5, p2.Y * 5 + 2, abs(p1.X - p2.X) * 10 - 1, color);
                return 1;

            }
            if (checkX(a, p2.Y, p1.Y + 1, p2.X, p2.X) && checkY(a, p2.X - 1, p1.X, p1.Y, p1.Y))
            {
                drawVerticalLine(p2.X * 10 + 4, p2.Y * 5 + 3, abs(p1.Y - p2.Y) * 5 - 1, color);
                gotoxy(p2.X * 10 + 4, p1.Y * 5 + 2);
                cout << (char)downleftcorn;
                drawHorizontalLine(p2.X * 10 + 5, p1.Y * 5 + 2, abs(p1.X - p2.X) * 10 - 1, color);
                return 1;
            }
        }
        if (p1.X < p2.X)
        {
            if (checkX(a, p2.Y - 1, p1.Y, p1.X, p1.X) && checkY(a, p1.X - 1, p2.X, p2.Y, p2.Y))
            {
                drawVerticalLine(p1.X * 10 + 4, p2.Y * 5 + 3, abs(p1.Y - p2.Y) * 5 - 1, color);
                gotoxy(p1.X * 10 + 4, p2.Y * 5 + 2);
                cout << (char)upleftcorn;
                drawHorizontalLine(p1.X * 10 + 5, p2.Y * 5 + 2, abs(p2.X - p1.X) * 10 - 1, color);
                return 1;
            }
            if (checkX(a, p2.Y, p1.Y + 1, p2.X, p2.X) && checkY(a, p1.X, p2.X + 1, p1.Y, p1.Y))
            {
                drawVerticalLine(p2.X * 10 + 4, p2.Y * 5 + 3, abs(p1.Y - p2.Y) * 5 - 1, color);
                gotoxy(p2.X * 10 + 4, p1.Y * 5 + 2);
                cout << (char)downrightcorn;
                drawHorizontalLine(p1.X * 10 + 5, p1.Y * 5 + 2, abs(p2.X - p1.X) * 10 - 1, color);
                return 1;
            }
        }
    }
    if (p1.Y < p2.Y)
    {
        if (p1.X > p2.X)
        {
            if (checkX(a, p1.Y, p2.Y + 1, p1.X, p1.X) && checkY(a, p2.X, p1.X + 1, p2.Y, p2.Y)) {
                drawVerticalLine(p1.X * 10 + 4, p1.Y * 5 + 3, abs(p2.Y - p1.Y) * 5 - 1, color);
                gotoxy(p1.X * 10 + 4, p2.Y * 5 + 2);
                cout << (char)downrightcorn;
                drawHorizontalLine(p2.X * 10 + 5, p2.Y * 5 + 2, abs(p1.X - p2.X) * 10 - 1, color);
                return 1;
            }
            if (checkX(a, p1.Y - 1, p2.Y, p2.X, p2.X) && checkY(a, p2.X - 1, p1.X, p1.Y, p1.Y)) {
                drawVerticalLine(p2.X * 10 + 4, p1.Y * 5 + 3, abs(p2.Y - p1.Y) * 5 - 1, color);
                gotoxy(p2.X * 10 + 4, p1.Y * 5 + 2);
                cout << (char)upleftcorn;
                drawHorizontalLine(p2.X * 10 + 5, p1.Y * 5 + 2, abs(p1.X - p2.X) * 10 - 1, color);
                return 1;

            }
        }
        if (p1.X < p2.X)
        {
            if (checkX(a, p1.Y, p2.Y + 1, p1.X, p1.X) && checkY(a, p1.X - 1, p2.X, p2.Y, p2.Y)) {
                drawVerticalLine(p1.X * 10 + 4, p1.Y * 5 + 3, abs(p2.Y - p1.Y) * 5 - 1, color);
                gotoxy(p1.X * 10 + 4, p2.Y * 5 + 2);
                cout << (char)downleftcorn;
                drawHorizontalLine(p1.X * 10 + 5, p2.Y * 5 + 2, abs(p2.X - p1.X) * 10 - 1, color);
                return 1;

            }
            if (checkX(a, p1.Y - 1, p2.Y, p2.X, p2.X) && checkY(a, p1.X, p2.X + 1, p1.Y, p1.Y)) {
                drawVerticalLine(p2.X * 10 + 4, p1.Y * 5 + 3, abs(p2.Y - p1.Y) * 5 - 1, color);
                gotoxy(p2.X * 10 + 4, p1.Y * 5 + 2);
                cout << (char)uprightcorn;
                drawHorizontalLine(p1.X * 10 + 5, p1.Y * 5 + 2, abs(p2.X - p1.X) * 10 - 1, color);
                return 1;

            }
        }
    }
    return 0;
}

int checkUDraw(board a, COORD p1, COORD p2, int boardSize, int color)
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
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y))
            {
                //drawVerticalLine(7 * 10, 1 * 10, 5, color);
                drawVerticalLine(i * 10 + 4, minY * 5 + 3, (maxY - minY) * 5 - 1, color);
                gotoxy(i * 10 + 4, minY * 5 + 2);
                cout << (char)uprightcorn;
                gotoxy(i * 10 + 4, maxY * 5 + 2);
                cout << (char)downrightcorn;
                drawHorizontalLine(p1.X * 10 + 5, p1.Y * 5 + 2, abs(i - p1.X) * 10 - 1, color);
                drawHorizontalLine(p2.X * 10 + 5, p2.Y * 5 + 2, abs(i - p2.X) * 10 - 1, color);


                Sleep(1000);
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
            if (checkY(a, p1.X, i, p1.Y, p1.Y) && checkY(a, p2.X, i, p2.Y, p2.Y))
            {
                //drawVerticalLine(7 * 10, 1 * 10, 5, color);
                drawVerticalLine(i * 10 + 4, minY * 5 + 3, (maxY - minY) * 5 - 1, color);
                gotoxy(i * 10 + 4, minY * 5 + 2);
                cout << (char)upleftcorn;
                gotoxy(i * 10 + 4, maxY * 5 + 2);
                cout << (char)downleftcorn;
                drawHorizontalLine(i * 10 + 5, p1.Y * 5 + 2, abs(p1.X - i) * 10 - 1, color);
                drawHorizontalLine(i * 10 + 5, p2.Y * 5 + 2, abs(p2.X - i) * 10 - 1, color);
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
                //drawVerticalLine(7 * 10, 1 * 10, 5, color);
                drawHorizontalLine(minX * 10 + 5, i * 5 + 2, (maxX - minX) * 10 - 1, color);
                gotoxy(minX * 10 + 4, i * 5 + 2);
                cout << (char)downleftcorn;
                gotoxy(maxX * 10 + 4, i * 5 + 2);
                cout << (char)downrightcorn;
                drawVerticalLine(p1.X * 10 + 4, p1.Y * 5 + 3, abs(i - p1.Y) * 5 - 1, color);
                //drawVerticalLine(p1.X * 10 + 4, p1.Y * 5 + 3, (i - p1.Y) * 5 - 1, color);
                drawVerticalLine(p2.X * 10 + 4, p2.Y * 5 + 3, abs(i - p2.Y) * 5 - 1, color);
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
                //drawVerticalLine(7 * 10, 1 * 10, 5, color);
                drawHorizontalLine(minX * 10 + 5, i * 5 + 2, (maxX - minX) * 10 - 1, color);
                gotoxy(minX * 10 + 4, i * 5 + 2);
                cout << (char)upleftcorn;
                gotoxy(maxX * 10 + 4, i * 5 + 2);
                cout << (char)uprightcorn;
                drawVerticalLine(p1.X * 10 + 4, i * 5 + 3, abs(p1.Y - i) * 5 - 1, color);
                drawVerticalLine(p2.X * 10 + 4, i * 5 + 3, abs(p2.Y - i) * 5 - 1, color);
                return 1;
            }

        }
    }
    return 0;
}

bool checkAndDraw(board a, COORD p1, COORD p2, int boardSize, int color)
{

    //drawVerticalLine(7 * 10 +3, 1 * 5, 5, color);
    //drawHorizontalLine(7 * 10, 2 * 5 + 2, 5, color);
    return (checkXDraw(a, p1.Y, p2.Y, p1.X, p2.X, color) || checkYDraw(a, p1.X, p2.X, p1.Y, p2.Y, color) || checkLDraw(a, p1, p2, color) || checkZDraw(a, p1, p2, color) || checkUDraw(a, p1, p2, 8, color));
}

bool helpFunc(board a, int boardSize, COORD& p1, COORD& p2)
{
    // tìm kiếm 1 ô giống nhau
    for (int i = 1; i < boardSize - 1; i++)
    {
        for (int k = 1; k < boardSize - 1; k++)
        {
            if (a[i][k].KeyinBox() != '0')
            {
                for (int n = 1; n < boardSize - 1; n++)
                {
                    for (int m = 1; m < boardSize - 1; m++)
                    {
                        if ((a[i][k].KeyinBox() == a[n][m].KeyinBox()) && (n != i || m != k))
                        {
                            p1.Y = i;
                            p1.X = k;
                            p2.Y = n;
                            p2.X = m;
                            if (checkAll(a, p1, p2, boardSize))
                                return 1;
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
    cout << endl;
    cout << "No more steps";
    return 0;
}

void shuffle(board& a, int boardSize)
{
    COORD p1, p2; // biến rác cho helpFunc
    do
    {
        // tìm những ô còn tồn tại và bỏ vô 1 mảng
        int n = (boardSize - 2) * (boardSize - 2) + 1, len = 0;
        char temp[100];
        char ka[8][8];
        for (int i = 1; i < boardSize - 1; i++)
        {
            for (int k = 1; k < boardSize - 1; k++)
            {
                if (a[i][k].KeyinBox() != '0') // kt nếu ô không trống thì thêm vào mảng tạm
                {
                    temp[len] = a[i][k].KeyinBox();
                    len++;
                    a[i][k].box[2][4] = '0';
                    a[i][k].key = '0';
                    ka[i][k] = '0';
                }
            }
        }
        // sắp xếp ngẫu nhiên những ô ở trên vào mảng
        for (int i = 0; i < len; i++)
        {
            int random1;
            int random2;
            do // lặp đến khi 1 ô được thêm ngẫu nhiên vào 1 vị trí trống
            {
                random1 = rand() % (boardSize - 2) + 1, random2 = rand() % (boardSize - 2) + 1; // tạo ngẫu nhiên địa chỉ
            } while (a[random1][random2].KeyinBox() != '0');
            a[random1][random2].box[2][4] = temp[i];
            a[random1][random2].key = temp[i];
            ka[random1][random2] = temp[i];
        }
    } while (!helpFunc(a, boardSize, p1, p2));
}
void shuffle2(board& a, int boardSize)
{
    COORD p1, p2; // biến rác cho helpFunc
    do
    {
        // tìm những ô còn tồn tại và bỏ vô 1 mảng
        int len = 0;
        char temp[100];
        COORD b[36]{ 0 };
        for (int i = 1; i < boardSize - 1; i++)
        {
            for (int k = 1; k < boardSize - 1; k++)
            {
                if (a[i][k].KeyinBox() != '0') // kt nếu ô không trống thì thêm vào mảng tạm
                {
                    temp[len] = a[i][k].KeyinBox();
                    b[len].Y = i;
                    b[len].X = k;
                    len++;
                }
            }
        }
        //trộn mảng 1 chiều đã lưu
        int minPosition;
        int maxPosition = len - 1;
        int swapPosition;
        int i = 0;
        while (i < len - 1)
        {
            minPosition = i + 1;
            swapPosition = rand() % (maxPosition - minPosition + 1) + minPosition;
            swap(temp[i], temp[swapPosition]);
            i++;
        }

        // sắp xếp ngẫu nhiên những ô ở trên vào mảng
        for (int i = 0; i < len; i++)
        {
            a[b[i].Y][b[i].X].key = temp[i];
            a[b[i].Y][b[i].X].box[2][4] = temp[i];
        }
    } while (!helpFunc(a, boardSize, p1, p2));
}
