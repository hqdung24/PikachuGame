#pragma once

#include "Menu.h"
#include "Console.h"
string MenuList[10]{ "     START   ", " RULES OF GAME ", "  LEADERBOARD  ", "     QUIT     "};

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
    gotoxy(x, 1);
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
 //   gotoxy(50, 23);
 //   SetConsoleTextAttribute(hConsole, 10);
 //   cout << R"(                
 //                                       ((( ((        
 //                                %@@@@@@&((((((((((@((      
 //                        @(((((((((((((((@(((((((((((       
 //                      (((((((((((((((((((((((((((&((       
 //       ******@******,#@/(((((*****,((((((((((((((((((      
 //      ***************,*************@((((((((((((((((((@    
 //     @*******&#######***************((((((((((((((((((((   
 //   @*********,###*******************&(((((((((((((((@((((  
 //  ** #*/*%#***************@/(*********@((((((((((((((((((( 
 // @  ((*&******&#(******,  ((@((**********((((((((((((((((( 
 // *  ( ********##/******  %((  (#*****/**####(((((((((((((( 
 //**  ((****************    ((((((*********######@(((((((((( 
 //*#********************,&@@****************&#####**@((((((  
 //  ***@**********************************************((     
 //      **&////////////////@*******&********&**********,     
 //       ***(****#@@@#*********#*****************##*****@    
 //       @***,@*********************##********(####/*****    
 //        /####****************@###*************####*****    
 //         ###********    ((((####,********(************&    
 //          *********      ( #*#&********    **********,     
 //           @   @            (* *****#       @   ,  @    )";
}


void choosePointer(int y, int choosing)
{
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14*choosing);
    gotoxy(39, y );
    cout << ">>" ;
    gotoxy(60, y);
    cout << "<<";
}

void printMenu(int x, int y, int cursor)
{
   
    int i = 0;
    int color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(x, y);
    while (i<4) {
        
        if (i == cursor)
        {//highlight background
            drawRectangle(42, y + i * 3, 17, 3, 0);
            color = 14;
            drawRectangle(41, y + i * 3, 19, 3, color);
            printText(MenuList[i], 43, y + i * 3 + 1, color);
            choosePointer(y + i * 3+1, 1);
        }
        else
        {
            drawRectangle(41, y + i * 3, 19, 3, 0);
            color = 11;
            drawRectangle(42, y + i * 3, 17, 3, color);
            printText(MenuList[i], 43, y + i * 3 + 1, color);
            choosePointer(y + i * 3 + 1, 0);
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

void printText(const string text, int x, int y, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    gotoxy(x, y);
    cout << text;
}

void drawRectangle(int x, int y, int width, int length, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == length - 1)
            {
                gotoxy(x + j, y + i);
                cout << (char)HorizontalDash;
            }
            if (j == 0 || j == width - 1)
            {
                gotoxy(x + j, y + i);
                cout << (char)VerticalDash;
            }
        }
    }
    gotoxy(x, y); cout << (char)upleftcorn;
    gotoxy(x + width - 1, y); cout << (char)uprightcorn;
    gotoxy(x + width - 1, y + length - 1); cout << (char)downrightcorn;
    gotoxy(x, y + length - 1); cout << (char)downleftcorn;
    SetConsoleTextAttribute(hConsole, 7);
}





