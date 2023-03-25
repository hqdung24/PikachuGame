#include <Windows.h>
#include <iostream>
using namespace std;
void gotoxy(int x, int y)// di chuyen con tro tren console de thuc hien cau lenh in
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(hConsole, cord);
}
void drawBackground(int x, int y)
{
    gotoxy(x, y);
    cout << R"(              &%%%%%%%                                                          
          &&&&/(((((((&%@@                                                      
        &&**////((((((((((@@                                                    
      &&*//////*((((((((((((@@                                                  
    &&((((((((((&&&%%&&&((((//&@                                                
    &%/(((((((((&&%%  ((%%/(((@@                                                
      &&/(((((((((&%  ((%%/(((&%                                                
    #(&&/(((((((((&%((((%%/(((&&@@                ((**    ((                    
    &%**((((((((((&&///(&&/(((&&@@                    ((**  **((                
  &%*//*((((((((((((((((((((&&&&@@                    ((********                
  &%**((((((((((((((((((((&%&&&&@@                    ((((******((              
  &%((&&/(&%((((((((%%@@%%&&&&&%                        ((((******((            
      #%@@@@%%%%&&&&&&&&%%&&&&@@      %&@&/*&&    , ((((**/(((/(((((((          
  &&&&      @@@@@@%%%%%%&&&&&&&&&&%%%%((&&**&%      ((((**((((((((**            
&&*/&&*/&&&&%%******&&&&&&&&&&&&&&/(((((((((%%      ((********((((**            
%%**/*((((((%%********&&&&&&&&&&&&/(((((((&&          /(**********((((          
    &%%%((%%            &&&&&&&&&&&&&&@@@@              ((**&&&&((((((          
        &%%%            &&&&&&&&@@@@@@                    &&&&&&/(((            
          &%            **&&&&&&&&@@                      &%&&&&                
        &&**            **&&&&&&&&@@                    &%*///&&                
        @@                &&&&&&&&&&@@              &&/**///@@                  
      %%@@                &&&&&&&&&&&&@@        &%&&((((*/@@                    
    &&/(@@              **&%((((&&&&&&@@%%%%%%&&/(((((((((@@                    
  &&/(((%%              &&/(((((((((&&&&%%&&&&&&&&/(((((@@                      
  &%((((((&%**        **@@/(((((((((&&&&@@&&&&&&&&,,@@                          
  &%&&/(&&&&%%**********@@&&/(((&&&&&&&&@@&&&&,,,,@@                            
    &%&&&&&&&&@@********@@&&&&&&&&&&&&&&@@,,,,@@@@                              
      &%&&&&&&&&@@%%******&%&&&&&&&&&&&&@@@@@@  
  %&&&(///&&&&&&@@          @@&%&&&&&&&&%&   
%%  &%  &%&&&&@@            &%/(((((&&&&@@  
  &%@@@@@@@@%%              @@  &%  &%  @@    
)";
}


int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Print some text to the console
    COORD pos;
    pos.X = 0;
    pos.Y = 5;
    drawBackground(0, 5);
    SetConsoleCursorPosition(hConsole, pos);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << 'c';
        }
        cout << endl;
    }

    // Erase a rectangular area of the console
    COORD topLeft;
    topLeft.X = 0;
    topLeft.Y = 5;
    DWORD numCharsWritten;
    for (int i = 0; i < 5; i++)
    {
        
        FillConsoleOutputCharacter(hConsole, ' ', 10, topLeft, &numCharsWritten);
        topLeft.Y++;
    }
    return 0;
}
