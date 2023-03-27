// PikachuGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StandardMode.h"
#include "Console.h"
#include "Menu.h"
using namespace std;

int main()
{
    ConsoleSetting();

    int choice = -1;
    do
    {
        system("CLS");
        printBanner();
        //drawBackground(100, 100);
        playSound(0);

        choice = MenuChoice();
        srand(time(0));
        switch (choice)
        {
        case 0:
        {
            playSound(-1);
            StandardMode1();
            break;
        }
        case 1:
        {
            system("CLS");
            cout << "ACCOUNT INFORMATION HERE";
            cin.ignore();
            break;
        }
        case 2:
        {
            cout << "LEADERBOARD HERE";
            cin.ignore();
            break;
        }
        case 3:
        {
            cout << " 3";
            break;
        }
        default:
        {
            choice = -1;
            break;
        }
        }
    } while (choice != 3);
}


