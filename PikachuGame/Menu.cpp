#pragma once

#include "Menu.h"
#include "Console.h"
string MenuList[10]{ "|    START    |", "|   ACCOUNT   |", "| LEADERBOARD |", "|    QUIT     |"};

void printBanner()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    cout << R"( 
                      ______   _____  _    _           ______  _     _  _     _ 
                     (_____ \ (_   _)| |  / )   /\    / _____)| |   | || |   | |
                      _____) )  | |  | | / /   /  \  | /      | |__ | || |   | |
                     |  ____/   | |  | |< <   / /\ \ | |      |  __)| || |   | |
                     | |       _| |_ | | \ \ | |--| || \_____ | |   | || |___| |
                     |_|      (_____)|_|  \_)|_|  |_| \______)|_|   |_| \______|
                                   
)";
    cout << right << setw(65) << "by: huyndungg && hoangkhangg ";
}

void drawBackground(int x, int y)
{
    gotoxy(100, 100);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout << R"(   
                 
                                                                          %%%%%                                    
                                                                     &&***(((((//@                                
                                                                    /*///(((&(((((%                               
                                                                   %((((((&&% (&%((@                              
                                                                   #&/((((((%#(%%((&@@          (*   (            
                                                                   &*(((((((&/(&&((&@@            (** *(          
                                                                  %/(((((((((((((%&&@@            (((***((        
                                                                   @&&&&&&%%% &&&&&@       &    (  ((((***(     
                                                                  &&    @@@@%%%&&&&&&&&&(&&/%    ((**(((((*       
                                                                %%/*(///%*****&&&&&&&&(((((&      (*******(    
                                                                   %%((%       &&&&&&&&&@@@        ((*&&(((     
                                                                       %       **&&&&&@              %&&          
                                                                     &%          &&&&&@           &***&           
                                                                    &@@          &&&&&&&@     &&&((/*@            
                                                                  &/(%%        &&(((///&&%%&&&&&(((@@             
                                                                  %((((%*     *@@((((((&&@@&&&&&,@                
                                                                   %&&&&&@*****@@&&&&&&&&@@,,@@@                  
                                                                   &&&&&&&&&@@@@@@&&&&&&@                         
                                                                && % &%&&@        %(///&&@@                                                                                              
                                
)";
    gotoxy(50, 23);
    SetConsoleTextAttribute(hConsole, 10);
    cout << R"(                
                                        ((( ((        
                                 %@@@@@@&((((((((((@((      
                         @(((((((((((((((@(((((((((((       
                       (((((((((((((((((((((((((((&((       
        ******@******,#@/(((((*****,((((((((((((((((((      
       ***************,*************@((((((((((((((((((@    
      @*******&#######***************((((((((((((((((((((   
    @*********,###*******************&(((((((((((((((@((((  
   ** #*/*%#***************@/(*********@((((((((((((((((((( 
  @  ((*&******&#(******,  ((@((**********((((((((((((((((( 
  *  ( ********##/******  %((  (#*****/**####(((((((((((((( 
 **  ((****************    ((((((*********######@(((((((((( 
 *#********************,&@@****************&#####**@((((((  
   ***@**********************************************((     
       **&////////////////@*******&********&**********,     
        ***(****#@@@#*********#*****************##*****@    
        @***,@*********************##********(####/*****    
         /####****************@###*************####*****    
          ###********    ((((####,********(************&    
           *********      ( #*#&********    **********,     
            @   @            (* *****#       @   ,  @    )";
}


void choosePointer(int x, int y, int cursor)
{
    gotoxy(40, y + cursor*3 + 1);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    cout << '>';
 
}

void printMenu(int x, int y, int cursor)
{
    gotoxy(x, y);
    int i = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    while (i<4) {
        if (i == cursor) //highlight background
        {
            cout << left << setw(42) << "";
            SetConsoleTextAttribute(hConsole, 14);
            for (int i = 0; i < 17; i++)
            cout << (char)VerticalDash;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 2);


            cout << left << setw(39) << "";
            SetConsoleTextAttribute(hConsole, 14);
            MenuList[i].insert(1, "  ");
            MenuList[i].insert(15, "  ");
            cout  << ">>" << MenuList[i] + "<<" << endl;
            MenuList[i].erase(1, 2);
            MenuList[i].erase(14, 2);
            SetConsoleTextAttribute(hConsole, 2);
            cout << left << setw(42) << "";
            SetConsoleTextAttribute(hConsole, 14);
            for (int i = 0; i < 17; i++)
            cout << (char)VerticalDash;
            cout << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 11);
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, 11);
            for (int i = 0; i < 15; i++)
            cout << (char)VerticalDash;
            cout << " ";
            cout << endl;

            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, 11);
            cout << MenuList[i]+"    " << endl;


            SetConsoleTextAttribute(hConsole, 11);
            cout << left << setw(43) << "";
            SetConsoleTextAttribute(hConsole, 11);
            for (int i = 0; i < 15; i++)
            cout << (char)VerticalDash;
            cout << " ";
            cout << endl;
        }
        i++;
    }
   
}

int MenuChoice() //MOVE UP AND DOWN, RETURN THE CHOICE
{
    char ch;
    
    int cursor = 0;

    int choice = 0;
    
    printMenu(0, 10, cursor);
    while (true) 
    {
        ch = _getch();
        if (ch == 72 && cursor != 0) 
        { // up arrow
            playSound(1);
            cursor--;
        }
        else if (ch == 80 && cursor < 4 - 1) 
        { // down arrow
            playSound(1);
            cursor++;
        }
        else if (ch == '\r')
        {//enter key
            playSound(2);
            Sleep(300);
            return cursor;
        }
        printMenu(0, 10, cursor);
    }
}







