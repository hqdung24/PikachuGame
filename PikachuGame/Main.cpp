// PikachuGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StandardMode.h"
#include "Console.h"
#include "Menu.h"
#include "Struct.h"
using namespace std;
Player playerlist[100];
int n = 1;


int main()
{
    
    playerlist[0].name = "haha";
    playerlist[0].password = "haha";
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


