#include "StandardMode.h"
#include <ctime>



board initialBoard(int ROWS, int COLS)
{
	board newboard = new cell* [ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		newboard[i] = new cell[COLS];
		//for (int j = 0; j < COLS; j++)
		//{
		//	
		//	newboard[i][j].key = (char)(rand() % 25 + 65);//CHUA CO THUAT TOAN TAO MAN CHOI NEN TAOO NGAU NHIEN
		//	newboard[i][j].box[2][4] = newboard[i][j].key;
		//}
	}
	return newboard;
}

void releaseBoard(board board, int ROWS, int COLS)
{
	for (int i = 0; i < ROWS; i++)
	{
		delete board[i];
	}
	delete board;
	board = NULL;
}

void drawBox(char cell[5][10], int ROWS, int COLS) //row, col of the board
{
	for (int i = 0; i < 5; i++) 
	{
		gotoxy( COLS * 10, ROWS * 4 + i); // X LA COT, Y LA HANG
		cout << cell[i] << endl;
	}
}



void drawTable(COORD cursor, board curboard, int ROWS, int COLS) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	int i = 0;
	static int s = 0;
	// loop through each cell in the table
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (row == cursor.Y && col == cursor.X) 
			{
				if (curboard[row][col].isSelected)
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);	
				else
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);// selected cell is highlight
			}
			else {
				if (curboard[row][col].isSelected)
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);
				else
					SetConsoleTextAttribute(hConsole, curboard[row][col].key % 15 + 1); // others cell are at their base colors
			}
			
			
			// print the cell contents
			if(curboard[row][col].box[2][4] != '0')
			drawBox(curboard[row][col].box, row, col);

		}
		// move to the next row
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 3);
	cout << "you are at : " << cursor.Y << " - " << cursor.X << " " << s <<  endl;
}

void getPosition(char input, COORD& CurPos, int ROWS, int COLS) //get coordinates of the cell and return
{
	if (input == 72 && CurPos.Y != 0) 
	{ // up arrow
		CurPos.Y--;
	}
	else if (input == 80 && CurPos.Y < ROWS - 1) 
	{ // down arrow
		CurPos.Y++;
	}
	else if (input == 75 && CurPos.X != 0) 
	{ // left arrow
		CurPos.X--;
	}
	else if (input == 77 && CurPos.X < COLS - 1) 
	{ // right arrow
		CurPos.X++;
	}
	else
		return;
}

int selectCell(char input, COORD& CurPos, board playingBoard)
{
	if (input == '\r') //press Enter
	{
		playingBoard[CurPos.Y][CurPos.X].isSelected = not playingBoard[CurPos.Y][CurPos.X].isSelected; 
		//press again to deselect
	}
	if (playingBoard[CurPos.Y][CurPos.X].isSelected) //selected
		return 1;
	else //deselect
		return -1;
}

void StandardMode1()
{
	
	system("CLS");
	COORD curpos{ 0, 0 };
	char input;
	board newboard = initialBoard(6, 6);
	generateBoard(newboard, 6, 6, 8);
	drawTable(curpos, newboard, 6, 6);

	int enterTime = 0; //so lan an enter

	while (true)
	{
		if (enterTime > 2)
		{
			newboard[curpos.Y][curpos.X].box[2][4] = '0';
			drawTable(curpos, newboard, 6, 6);
			enterTime = 0;
		}
		input = _getch();
		getPosition(input, curpos, 6, 6);//curpos is updated
		enterTime += selectCell(input, curpos, newboard); //if press enter at current cell, the cell will be selected
		drawTable(curpos, newboard, 6, 6);
		if (input == 27) break;
	}
}


void generateBoard(board& curboard, int ROWS, int COLS, int amountpoke) 
{

	int * typeLimit = new int[8];
	//min xài để đếm số lượng tối thiểu 1 pokemon sẽ xuất hiện
	int minPoke = (ROWS * COLS) / amountpoke;
	//excess dùng để tính có bao nhiêu pokemon sẽ dc +2 vào số lượng có thể dc xuất hiện
	int excessPoke = ((ROWS * COLS) % amountpoke) / 2;
	//phân bổ số lượng vào từng pokemon
	for (int i = 0; i < amountpoke; i++)
	{
		typeLimit[i] = minPoke;
	}
	//chọn ngẫu nhiên những pokemon dc xuất hiện nhiều hơn 
	for (int i = 0; i < excessPoke; i++)
	{
		typeLimit[rand() % amountpoke] += 2;
	}

	int type[8] = { 1, 2, 3, 4, 5, 6, 7, 8};
	int countType[8] = { 0, 0, 0, 0, 0, 0, 0,0 };
	//khai báo mảng động
	
	//Tạo phần tử ngẫu nhiên
	for (int i = 0; i < ROWS; i++) {
		for (int k = 0; k < COLS; k++)
		{
			int random;
			do {
				random = rand() % 8;
			} while (countType[random] >= typeLimit[random]);
			curboard[i][k].key = (char)(65+type[random]);
			curboard[i][k].box[2][4] = curboard[i][k].key;
			countType[random]++;
		}

	}
}



