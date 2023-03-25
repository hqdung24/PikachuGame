
#include "Console.h"
//Di chuyển đến tọa độ (x, y) trong console
void gotoxy(int x, int y)// di chuyen con tro tren console de thuc hien cau lenh in
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(hConsole, cord);
}


//Thay đổi Windows Size
void SetWindowSize(SHORT width, SHORT height) 
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}


//Thay đổi Screen Buffer Size
void SetScreenBufferSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}


//Vô hiệu hóa thu phóng kích thước cửa sổ
void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}


//Ẩn hiện thanh cuộn
void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}


//Ẩn hiện con trỏ
void ShowCur(bool CursorVisibility)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = false; // set the cursor visibility to false
    SetConsoleCursorInfo(consoleHandle, &info);
}


//Vô hiệu hóa bôi đen text
void DisableSelection()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

void setAndCenterWindow()
{
    RECT rectClient, rectWindow;
    HWND consoleWindow = GetConsoleWindow();
    GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
    int width = 1100;
    int height = 768;
    int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
        posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}



void ConsoleSetting()
{
    SetConsoleTitle(L"PikachuGame.exe");

    SetWindowSize(80, 60);
    SetScreenBufferSize(100, 50);
    //DisableResizeWindow();
    ShowScrollbar(0);
    ShowCur(0);
    setAndCenterWindow();
    DisableSelection();
}
