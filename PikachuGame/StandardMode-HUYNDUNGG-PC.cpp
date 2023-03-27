#include "StandardMode.h"
#include <ctime>


board initialBoard(int ROWS, int COLS)
{
	board newboard = new cell* [ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		newboard[i] = new cell[COLS];
		for (int j = 0; j < COLS; j++)
		{
			newboard[i][j].ldashchange();
		}
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
		gotoxy(6 + COLS * 10, ROWS * 5 + i); // X LA COT, Y LA HANG
		cout << cell[i] << endl;
	}
}

void drawdeBox(char cell[5][10], int ROWS, int COLS) //draw deleted box
{
	for (int i = 0; i < 5; i++)
	{
		gotoxy(COLS * 10, ROWS * 5 + i); // X LA COT, Y LA HANG
		cout << '\b' << endl;
	}
}

void drawMargin(board board, int ROWS, int COLS) //draw the margin of the board
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 7) board[i][j].deBox();
			else 
			{
				if(j == 0 || j == 7)
					 board[i][j].deBox();
			}
		}
	}
}

void drawTable(COORD cursor, board curboard, int ROWS, int COLS, COORD selpos[], int enterTime)
{
	system("CLS");
	//gameBackground(10, 5);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	int i = 0;
	static int s = 0;
	int emptycell = 0;
	// loop through each cell in the table
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (row == cursor.Y && col == cursor.X) //ô đang chứa cursor
			{
				if (curboard[row][col].isSelected) 
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN );	//nếu ô được chọn thì tô vàng
				else if (curboard[row][col].KeyinBox() == '0') //ô đã xóa vẫn tô xanh chữ xanh để theo dõi con trỏ 
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN);
					drawBox(curboard[row][col].box, row, col);
				}
				else //ô chưa xóa tô xanh chữ đỏ 
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);// tô xanh
			}
			else  //các ô còn lại
			{
				if (curboard[row][col].isSelected)//nếu ô được chọn
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);
				
				else 
					SetConsoleTextAttribute(hConsole, curboard[row][col].key % 15 + 1); // others cell are at their base colors
			}
			
			
			// print the cell contents
			if (curboard[row][col].KeyinBox() != '0') //ô đã xóa vẫn tô xanh chữ xanh để theo dõi con trỏ 
			{
				drawBox(curboard[row][col].box, row, col);
			}
				
		
		}
		// move to the next row
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 3);
	cout << endl;
	cout << "you are at : " << cursor.Y << " - " << cursor.X << " " << s <<  endl;
}

void getPosition(char input, COORD& CurPos, int ROWS, int COLS) //get coordinates of the cell and return
{
	if (input == 72 && CurPos.Y != 1) 
	{ // up arrow
		CurPos.Y--;
	}
	else if (input == 80 && CurPos.Y < ROWS - 2) 
	{ // down arrow
		CurPos.Y++;
	}
	else if (input == 75 && CurPos.X != 1) 
	{ // left arrow
		CurPos.X--;
	}
	else if (input == 77 && CurPos.X < COLS - 2) 
	{ // right arrow
		CurPos.X++;
	}
	else
		return;
}



int selectCell(char input, COORD CurPos, board playingBoard)
{
	if (input == '\r') //press Enter
	{
		if (playingBoard[CurPos.Y][CurPos.X].KeyinBox() != '0') //Ô đã xóa ko được phép chọn
		return playingBoard[CurPos.Y][CurPos.X].select() ;
		//press again to deselect
	}
	return 0;
}

void gameBackground(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	gotoxy(x, y);
	cout << R"(
		GGGP5PBBBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
		GBP~^~7YGBBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
		GBG~^^^^~?PBBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
		GGG!^^^~JY!75BBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
		GGGJ^^~PBBBY!7PBBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
		GGGP~^P#BBBBBJ~?GBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
		GGPGY^JBBBBBBBG7!5BGGGGGGGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBB
		GGGPGY~?GBBBBBBBY~JBBBBBBBBBBBBBBBBBBBGGGGBBBBGP5YYJJJ?JJYY
		GGGGPG5!!5BBBBBBBP~7GP5YJJJJ?JJJJYY5PGGBBBG5J?7?JY55PPJ~:^^
		GGGGGPGGY!75BBBBBBG!~?JY55PPPPPP55YJ?77JJ77J5GBBBBBBBB#BY~^
		GGGGGGPGGPY7!JPBBBBBPBBBBBBBBBBBBBBB#BP!?PBBBBBBBBBBBBBP57~
		GGGGGGGGPGGGY^!JBBBBBBBBBBBBBBBBBBBB#####BBBBBBBBGP5J?77?YP
		GGGGGGGGGGGP!?GBBBBBBBBBBBBBBBBBBBBBBBB###BGYYJ?777?J5PGGGG
		GGGGGGGGGGGYYGBBBBBBBBBBBBBBBBBBBBBBBBBBB##GY~!5PPGGGGGGGGG
		GGGGGGGGGBP?5GBBBBBBBBBBBBBBBBBBBBBBBBBBBB###J~PGGGGGGGGGGG
		GGGGGGGGGGJ^PBBBBGPPGBBBBBBBBBBBBBBBBBPPPB##BP^5BGGGGGGGGGG
		GGGGGGGGGG!!GBBB?~G#?JBBBBBBBBBBBBBBP!G#?~PBBB~?BGGGGGGGGGG
		GGGGGGGGG5^JBBBG~^77^7BBBBBBBBBBBBBB5^!?~^5BBB?~GBGGGGGGGGG
		GGGGGGGGG7~GBBB#GY?J5BBBBBBP!!JBBBBBBPJ?JPBBB#G~JBGGGGGGGGG
		GGGGGGGBP~?P5YY5PB#BBBBPBBBB5JGBBBGGBBB#BP5YY5G7!BGGGGGGGGG
		GGGGGGGGG!~?7????JPBBBBY77?7!~7??7JPBBBP???????~?BGGGGGGGGG
		GGGGGGGGGY^!?7????JBBBB#J^^!77!~^~BBBBB???????!~PBGGGGGGGGG
		GGGGGGGGPGY~!777??PBBBBBG~?5555Y~JBBBBB5?????!~5BGGGGGGGGGG
		GGGGGGGGGGG57~!?5GBBBBBBBP7?JJJ7JBBBBBB#B5J!~?GBGGGGGGGGGGG
		GGGGGGGGGGPGG5?77?YPGGBBBBBP555G#BBBBBG5J77JPBBGGGGGGGGGGGG
		GGGGGGGGGGGGPGGP5J?77?JY55PGGGGPP5YJ?77?YPGBBGGGGGGGGGGGGGG
		GGGGGGGGGGGGGGGGGGGGP5YJ??777777??JY5PGGGGGGGGGGGGGGGGGGGGG
		GGGGGGGGGGGGGGGGGGGGGGGGGGGPPPPGGGGGGGGGGGGGGGGGGGGGGGGGGGG
)";
}

COORD IndexOfSelPos(int enterTime, COORD CurPos, board curBoard)
{
	 return CurPos;
}


void StandardMode1()
{
	int enterTime = -1; //so lan an enter
	int emptycell = 0;
	char input;

	COORD curpos{ 1, 1 };//vị trí của con trỏ trên bảng
	COORD selpos[2]{ 0 };//vị trí của 2 con trỏ được chọn dùng để xóa
	board newboard = initialBoard(8, 8);

	//initial a board
	system("CLS");
	generateBoard(newboard, 8, 8, 8);
	drawMargin(newboard, 8, 8);
	drawTable(curpos, newboard, 8, 8, selpos, 0);
	

	//move cursor in the board
	while (emptycell < 36)
	{			
		fflush(stdin);
				input = _getch();
				getPosition(input, curpos, 8, 8);//curpos is updated
				enterTime += selectCell(input, curpos, newboard);

				if (enterTime == 0 && newboard[curpos.Y][curpos.X].isSelected == 1)
				{
					selpos[0].Y = curpos.Y;
					selpos[0].X = curpos.X;
				}
				else if (enterTime == 1) //khi co 2 o duoc chon
				{
						selpos[1].Y = curpos.Y;
						selpos[1].X = curpos.X;


						if (checkAll(newboard, selpos[0], selpos[1],8) == 1 && newboard[selpos[0].Y][selpos[0].X].KeyinBox() == newboard[selpos[1].Y][selpos[1].X].KeyinBox())//khi co thuat toan check I U Z L se thay the dong code nay	
						{						
							newboard[selpos[0].Y][selpos[0].X].deBox();
							newboard[selpos[1].Y][selpos[1].X].deBox();
							emptycell += 2;
							enterTime = -1;	
						}
						else 
						{
							newboard[selpos[0].Y][selpos[0].X].select();
							newboard[selpos[1].Y][selpos[1].X].select();
							enterTime = -1;
						}
				}
				//đống này để test cái helpFunc
				// COORD p1,p2;
				// helpFunc(newboard,8, p1, p2);
				// cout << endl;
				// cout << "Point 1: " << p1.X << "-" << p1.Y << "Point 2: " << p2.X << "-" << p2.Y;
				// system("pause");
				//if press enter at current cell, the cell will be selected
				drawTable(curpos, newboard, 8, 8, selpos, enterTime);
				gotoxy(0, 60); 
				cout << enterTime << endl << emptycell << endl;


	}
	cout << "YOU WON.....................";
	cin.ignore();
}



void generateBoard(board& curboard, int ROWS, int COLS, int amountpoke) 
{
	int temp = ROWS - 2;
	int * typeLimit = new int[temp];
	//min xài để đếm số lượng tối thiểu 1 pokemon sẽ xuất hiện
	int minPoke = (temp * temp) / amountpoke;
	//excess dùng để tính có bao nhiêu pokemon sẽ dc +2 vào số lượng có thể dc xuất hiện
	int excessPoke = ((temp * temp) % amountpoke) / 2;
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
	for (int i = 1; i < ROWS - 1; i++) {
		for (int k = 1; k < COLS - 1; k++)
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
 


