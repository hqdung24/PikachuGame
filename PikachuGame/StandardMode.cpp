#include "StandardMode.h"


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


board initialBoard(int ROWS, int COLS)
{
	board newboard = new cell* [ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		newboard[i] = new cell[COLS];
		for (int j = 0; j < COLS; j++)
		{
			newboard[i][j].renderbox();
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

void drawBox(char cell[5][10], int row, int col) //row, col of the board
{
	
	for (int i = 0; i < 5; i++) 
	{
		gotoxy( col * 10, row * 5 + i); // X LA COT, Y LA HANG
		cout << cell[i] << endl;
	}
}

void setMargin(board board, int ROWS, int COLS) //draw the margin of the board
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 7) 
			{
				board[i][j].box[2][4] = '0';
				board[i][j].key = '0';
			}
			else 
			{
				if (j == 0 || j == 7)
				{
					board[i][j].box[2][4] = '0';
					board[i][j].key = '0';
				}
			}
		}
	}
}

void drawSubTable(int x, int y, int width, int length, int score)
{
	//SCORE table
	drawRectangle(x - 5, y, width + 10, length * 3 + 5, 13);
	drawRectangle(x, y + 1, width, length, WHITE);
	printText("SCORE : ", x + 3, y + 2, RED);
	printText(to_string(score), x + 14, y + 2, GREEN);
	y += 1 + length; //draw table vertically    

	drawRectangle(x - 4, y, width + 8, length * 3, WHITE);
	y++;
	printText(" <SHORTCUTS>", x + 3, y++, LIGHT_RED);
	printText("S : SURRENDER", x - 2, y++, LIGHT_GREEN);
	printText("H : GET A MOVE SUGGESTION", x - 2, y++, LIGHT_AQUA);
	printText("L : VIEW LEADERBOARD", x - 2, y++, LIGHT_YELLOW);
	printText("M : TURN OFF MUSIC", x - 2, y++, LIGHT_PURPLE);
	printText("R : READ RULE OF GAME", x - 2, y++, YELLOW);
}

void drawTable(COORD cursor, COORD helpp[2], board curboard, int ROWS, int COLS)
{

	int i = 0;
	static int s = 0;
	int emptycell = 0;
	// loop through each cell in the table
	for (int row = 1; row < ROWS - 1; row++) {
		for (int col = 1; col < COLS - 1; col++) {
			if (row == cursor.Y && col == cursor.X) //ô đang chứa cursor
			{
				if (curboard[row][col].isSelected)
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);	//nếu ô được chọn thì tô vàng
				else if (curboard[row][col].KeyinBox() == '0') //ô đã xóa vẫn tô xanh chữ xanh để theo dõi con trỏ 
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN);
					//drawBox(curboard[row][col].box, row, col);
				}
				else //ô chưa xóa tô xanh chữ đỏ 
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);// tô xanh
			}
			else  //các ô còn lại
			{
				if (curboard[row][col].isSelected)//nếu ô được chọn
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);
				else if (curboard[row][col].KeyinBox() == '0')
				{
					SetConsoleTextAttribute(hConsole, 0);
				}
				else
					SetConsoleTextAttribute(hConsole, curboard[row][col].key % 15 + 1); // others cell are at their base colors
			}
			if ((row == helpp[0].Y && col == helpp[0].X) || (row == helpp[1].Y && col == helpp[1].X)) //ô gợi ý
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BACKGROUND_BLUE);

			// print the cell contents

			drawBox(curboard[row][col].box, row, col);

		}
		// move to the next row
		cout << endl;
	}
	//SetConsoleTextAttribute(hConsole, 3);
	/*cout << endl;
	cout << "you are at : " << cursor.Y << " - " << cursor.X << " " << s << endl;*/
}

void drawBoardAtStart(board cur, int ROWS, int COLS)
{
	int h1 = 1;
	int h2 = ROWS - 2;
	int c1 = 1;
	int c2 = COLS - 2;
	Sleep(200);
	gameBackground(10, 5);
	while (h1 <= h2 && c1 <= c2)
	{
		for (int i = c1; i <= c2; i++)
		{
			playSound(4);
			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);
			drawBox(cur[h1][i].box, h1, i);
			Sleep(100);
			SetConsoleTextAttribute(hConsole, cur[h1][i].key % 15 + 1);
		    drawBox(cur[h1][i].box, h1, i);
		}
		h1++;
		for (int i = h1; i <= h2; i++)
		{
			playSound(4);
			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
			drawBox(cur[i][c2].box, i, c2);
			Sleep(100); 

			SetConsoleTextAttribute(hConsole, cur[i][c2].key % 15 + 1);
		   drawBox(cur[i][c2].box, i, c2);
		}
		c2--;
		if (c1 <= c2)
		{
			for (int i = c2; i >= c1; i--)
			{
				playSound(4);
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
				drawBox(cur[h2][i].box, h2, i);

				Sleep(100); 

				SetConsoleTextAttribute(hConsole, cur[h2][i].key % 15 + 1);
				 drawBox(cur[h2][i].box, h2, i);
			}
			h2--;
		}
		if (h1 <= h2)
		{
			for (int i = h2; i >= h1; i--)
			{
				playSound(4);
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
				drawBox(cur[i][c1].box, i, c1);
				Sleep(100); 

				SetConsoleTextAttribute(hConsole, cur[i][c1].key % 15 + 1);
				drawBox(cur[i][c1].box, i, c1);
			}
			c1++;
		}
	}
	/* SetConsoleTextAttribute(hConsole, 16 * 11 + 11);
	for (int i = 0; i < 5 * 6; i++)
	{
		gotoxy(15, 5+i);
		for (int j = 0; j < 10 * 6; j++)
			cout << "c";
		cout << endl;
	}*/
}

void drawNotiTable(int x, int y, int width, int length, COORD cursor, COORD helpp[2], char input)
{
	drawRectangle(x - 5, y, width + 10, length * 3 + 5, LIGHT_BLUE);
	drawRectangle(x, y + 1, width, length, WHITE);
	printText("NOTIFICATION", x + 4, y + 2, LIGHT_BLUE);
	y += 1 + length; //draw table vertically    

	drawRectangle(x - 4, y, width + 8, length * 3, WHITE);
	y++;
	
	printText(" YOU ARE AT CELL ", x-2 , y, LIGHT_YELLOW);
	gotoxy(x + 15, y++); cout << "[" << cursor.Y << "]" << "[" << cursor.X << "]";
	/*printText("S : SURRENDER", x - 2, y++, LIGHT_GREEN);
	printText("H : GET A MOVE SUGGESTION", x - 2, y++, LIGHT_AQUA);*/
	/*printText("L : VIEW LEADERBOARD", x - 2, y++, LIGHT_YELLOW);
	printText("M : TURN OFF MUSIC", x - 2, y++, LIGHT_PURPLE);
	printText("R : READ RULE OF GAME", x - 2, y++, YELLOW);*/
}

void getPosition(char input, COORD& CurPos, int ROWS, int COLS) //get coordinates of the cell and return
{
	if (input == 72 && CurPos.Y !=1) 
	{ // up arrow
		playSound(1);
		CurPos.Y--;
	}
	else if (input == 80 && CurPos.Y < ROWS - 2) 
	{ // down arrow
		playSound(1);
		CurPos.Y++;
	}
	else if (input == 75 && CurPos.X != 1) 
	{ // left arrow
		playSound(1);
		CurPos.X--;
	}
	else if (input == 77 && CurPos.X < COLS - 2) 
	{ // right arrow
		playSound(1);
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

void generateBoard(board& curboard, int ROWS, int COLS, int amountpoke)
{
	int temp = ROWS - 2;
	int* typeLimit = new int[temp];
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

	int type[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
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
			curboard[i][k].key = (char)(65 + type[random]);
			curboard[i][k].box[2][4] = curboard[i][k].key;
			countType[random]++;
		}

	}
}
 


void StandardMode1()
{
	int enterTime = -1; //so lan an enter
	int emptycell = 8*8 - 6*6;
	char input;
	int score = 0;

	COORD curpos{ 3, 4 };//vị trí của con trỏ trên bảng
	COORD selpos[2]{ -1,-1};//vị trí của 2 con trỏ được chọn để nối với nhau
	COORD helppos[2]{ -1,-1, -1, -1 }; //vị trí của 2 ô được gợi ý 
	board newboard = initialBoard(8, 8);

	
	system("CLS");
	//setMargin(newboard, 8, 8);

	//initial a board
	generateBoard(newboard, 8, 8, 8);

	
	//drawBoardAtStart(newboard, 8, 8);
	drawSubTable(86, 5, 20, 3, score);
	drawTable(curpos, helppos, newboard, 8, 8);
	drawRectangle(8, 4, 63, 32, WHITE);

	//move cursor in the board/
	while (emptycell < 8*8)
	{			
		drawSubTable(86, 5, 20, 3, score);
		drawNotiTable(86, 21, 20, 3, curpos, helppos, 'o');
		fflush(stdin);

		

		input = _getch();//nhận lệnh từ bàn phím

		if (input == 'm') //kiểm tra có còn đường đi hay không
		{
			shuffle(newboard, 8);

		}
		getPosition(input, curpos, 8, 8);//xu ly khi an phim mui ten de di chuyen
		enterTime += selectCell(input, curpos, newboard);
		if (enterTime == 0 && newboard[curpos.Y][curpos.X].isSelected == 1)//xu ly khi an enter lan 1
		{
			playSound(2);
			selpos[0].Y = curpos.Y;
			selpos[0].X = curpos.X;
		}
		else if (enterTime == 1) //xu ly khi an enter lan 2
		{
			selpos[1].Y = curpos.Y;
			selpos[1].X = curpos.X;
			if (checkAll(newboard, selpos[0], selpos[1], 8) == 1 && newboard[selpos[0].Y][selpos[0].X].KeyinBox() == newboard[selpos[1].Y][selpos[1].X].KeyinBox())//khi co thuat toan check I U Z L se thay the dong code nay	
			{
				playSound(2);
				newboard[selpos[0].Y][selpos[0].X].deBox();
				newboard[selpos[1].Y][selpos[1].X].deBox();
				emptycell += 2;
				enterTime = -1;
				score += 2;
			}
			else
			{
				playSound(6);
				newboard[selpos[0].Y][selpos[0].X].select();
				newboard[selpos[1].Y][selpos[1].X].select();
				enterTime = -1;
			}
		}

		if (input == 'h')
		{
			playSound(1);
			helpFunc(newboard, 8, helppos[0], helppos[1]);
			drawTable(curpos, helppos, newboard, 8, 8);
			/*gotoxy(0, 41);
			cout << helppos[0].Y << " " << helppos[0].X<< helppos[1].Y << " " << helppos[1].X;*/
			Sleep(500);
			//reset suggestion position
			helppos[0] = { -1, -1 };
			helppos[1] = { -1, -1 };
			drawTable(curpos, helppos, newboard, 8, 8);
		}else
		//reset suggestion position
		//helppos[0] = { -1, -1 };
		//helppos[1] = { -1, -1 };
		drawTable(curpos, helppos, newboard, 8, 8);
		
	}
	system("CLS");
	playSound(7);
	gotoxy(10, 5);
	cout << "YOU WON.....................";
	Sleep(3000);
	releaseBoard(newboard, 8, 8);
}
