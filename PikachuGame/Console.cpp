﻿#include "Console.h"


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
    info.bVisible = CursorVisibility; // set the cursor visibility to false
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
        posY = (GetSystemMetrics(SM_CYSCREEN) - height) /2;
    MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}


void ConsoleSetting()
{
    SetConsoleTitle(L"The Matching Game");
    //SetWindowSize(100, 45);
    //SetScreenBufferSize(150, 45);
    setAndCenterWindow();
    DisableResizeWindow();
    ShowScrollbar(0);
    ShowCur(0);
    DisableSelection();
}


//-1 turn off background music
//0 - MenuMusic
//1 - move
//2 - Enter
//3 - ingame Music
//4 - cell running sound
//5 - success delete 2 cell
//6 - fail delete 2 cell
//7 - winning
void playSound(int id, int toggle) //1 to play, -1 to pause
{
    if (toggle == -1)
    {
        static vector<const wchar_t*> soundFile1{ L"pause MenuMusic.wav", L"pause move.wav", L"pause enter.wav", L"pause ingameBackground1.wav", L"pause createBoardSound.wav",  L"pause SuccessDelete2Cells.wav", L"pause FailDelete2Cells.wav", L"pause winningSound.wav" };
        mciSendString(soundFile1[id], NULL, 0, 0);
    }
    else {
        static vector<const wchar_t*> soundFile2{ L"play MenuMusic.wav", L"play move.wav", L"play enter.wav", L"play ingameBackground1.wav", L"play createBoardSound.wav",  L"play SuccessDelete2Cells.wav", L"play FailDelete2Cells.wav", L"play winningSound.wav" };
        mciSendString(soundFile2[id], NULL, 0, 0);
    }
}
