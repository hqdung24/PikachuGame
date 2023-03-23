#include "Struct.h"
#include <wincon.h>
#include <conio.h>
typedef cell** board;
board initialBoard(int ROWS, int COLS);
void getPosition(char input, COORD& CurPos, int ROWS, int COLS);
int selectCell(char input, COORD& CurPos, board playingBoard);


void drawBox(char cell[5][10], int ROWS, int COLS);

void drawTable(COORD cursor, board b, int ROWS, int COLS);

void StandardMode1();

void releaseBoard(board board, int ROWS, int COLS);
void generateBoard(board& curboard, int ROWS, int COLS, int amountpoke);