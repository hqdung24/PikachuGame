// PikachuGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StandardMode.h"
#include "Console.h"
#include "Menu.h"
#include "Struct.h"
using namespace std;
Player playerlist[100];
int n = 6;


int main()
{
    int temp = 15;
    playerlist[0].name = "dung1";
    playerlist[0].password = "haha";
    playerlist[0].record.points = temp--;
    playerlist[1].name = "dung2";
    playerlist[1].password = "haha";
    playerlist[1].record.points = temp--;
    playerlist[2].name = "dung3";
    playerlist[2].password = "haha";
    playerlist[2].record.points = temp--;
    playerlist[3].name = "dung4";
    playerlist[3].password = "haha";
    playerlist[3].record.points = temp--;
    playerlist[4].name = "dung5";
    playerlist[4].password = "haha";
    playerlist[4].record.points = temp--;
    playerlist[5].name = "dung6";
    playerlist[5].password = "haha";
    playerlist[5].record.points = temp--;
    srand(time(0));
    ConsoleSetting();
    int playerindex = -1;
    while (true)
    {
        system("CLS");
        //printBanner("");
        drawBackground(100, 5);
        //playSound(0, 1);
        playerindex = StartMenuChoice(playerlist, n);
        if (playerindex == -1) break;
        game(playerlist, n, playerindex);
    }   
}


