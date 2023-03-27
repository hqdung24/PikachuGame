#pragma once
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <vector>

using namespace std;


void gotoxy(int x, int y);

void SetWindowSize(SHORT width, SHORT height);

void SetScreenBufferSize(SHORT width, SHORT height);

void DisableResizeWindow();

void ShowScrollbar(BOOL Show);

void ShowCur(bool CursorVisibility);

void DisableSelection();

void ConsoleSetting();

void setAndCenterWindow();

void playSound(int); //choose id of sound effect list, return 1 if succesfully play the sound
