﻿#include "StandardMode.h"


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
void drawdeBox(char cell[5][10], int row, int col) //row, col of the board
{
	for (int i = 0; i < 5; i++)
	{
		 // X LA COT, Y LA HANG
		gotoxy(col * 10, row * 5 + i); // X LA COT, Y LA HANG
		cout << "         " << endl;
	}
}

void setMargin(board board, int ROWS, int COLS) //draw the margin of the board
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i == 0 || i == ROWS - 1) 
			{
				board[i][j].box[2][4] = '0';
				board[i][j].key = '0';
			}
			else 
			{
				if (j == 0 || j == COLS - 1)
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
	printText("F : SAVE GAME AND QUIT", x - 2, y++, LIGHT_GREEN);
	printText("Q : GET A MOVE SUGGESTION", x - 2, y++, LIGHT_AQUA);
	printText("S : SHUFFLE THE BOARD", x - 2, y++, LIGHT_YELLOW);
	printText("O : TURN OFF MUSIC", x - 2, y++, LIGHT_PURPLE);

}

void drawDeTable(char cell[5][10], int ROWS, int COLS)
{
	for (int row = 1; row < ROWS - 1; row++) 
	{
		for (int col = 1; col < COLS - 1; col++)
		{
			drawdeBox(cell, row, col);
		}
	}

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
				}
				else //ô chưa xóa tô xanh chữ đỏ 
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);// tô xanh
			}
			else  //các ô còn lại
			{
				if (curboard[row][col].isSelected)//nếu ô được chọn
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN);
					drawBox(curboard[row][col].box, row, col);
				}
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
}

void drawBoardAtStart(board cur, int ROWS, int COLS)
{
	int h1 = 1;
	int h2 = ROWS - 2;
	int c1 = 1;
	int c2 = COLS - 2;
	//Sleep(200);
	//gameBackground(10, 5);
	while (h1 <= h2 && c1 <= c2)
	{
		for (int i = c1; i <= c2; i++)
		{
			
			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);
			drawBox(cur[h1][i].box, h1, i);
			Sleep(100);
			PlaySound(L"createBoardSound", NULL, SND_FILENAME | SND_ASYNC);
			SetConsoleTextAttribute(hConsole, cur[h1][i].key % 15 + 1);
		    drawBox(cur[h1][i].box, h1, i);
		}
		h1++;
		for (int i = h1; i <= h2; i++)
		{
			
			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
			drawBox(cur[i][c2].box, i, c2);
			Sleep(100); 
			PlaySound(L"createBoardSound", NULL, SND_FILENAME | SND_ASYNC);
			SetConsoleTextAttribute(hConsole, cur[i][c2].key % 15 + 1);
		    drawBox(cur[i][c2].box, i, c2);
		}
		c2--;
		if (c1 <= c2)
		{
			for (int i = c2; i >= c1; i--)
			{
				
			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
			drawBox(cur[h2][i].box, h2, i);

			Sleep(100); 
			PlaySound(L"createBoardSound", NULL, SND_FILENAME | SND_ASYNC);
			SetConsoleTextAttribute(hConsole, cur[h2][i].key % 15 + 1);
			drawBox(cur[h2][i].box, h2, i);
			}
			h2--;
		}
		if (h1 <= h2)
		{
			for (int i = h2; i >= h1; i--)
			{
				
			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE);
			drawBox(cur[i][c1].box, i, c1);
			Sleep(100); 
			PlaySound(L"createBoardSound", NULL, SND_FILENAME | SND_ASYNC);
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

void drawNotiTable(int x, int y, int width, int length, string outputline1, string outputline2, string outputline3)
{
	drawRectangle(x - 5, y, width + 10, length * 3 + 5, LIGHT_BLUE);
	drawRectangle(x, y + 1, width, length, WHITE);
	printText("NOTIFICATION", x + 4, y + 2, LIGHT_BLUE);
	y += 1 + length; //draw table vertically    

	drawRectangle(x - 4, y, width + 8, length * 3, WHITE);
	y++;
	for (int j = 0; j < 6; j++)
	{
		SetConsoleTextAttribute(hConsole, 0);
		gotoxy(x - 3, y + j); cout << "cccccccccccccccccccccccccc";
	}
		printText(outputline1, x-2, y + 2, LIGHT_YELLOW);
		printText(outputline2, x-2, y + 3, LIGHT_YELLOW);
		printText(outputline3, x-2, y + 4, LIGHT_YELLOW);
	
}

void getPosition(char input, COORD& CurPos, int ROWS, int COLS) //get coordinates of the cell and return
{
	if (input == 72 && CurPos.Y !=1) 
	{ // up arrow
		playSound(1, 1);
		CurPos.Y--;
	}
	else if (input == 80 && CurPos.Y < ROWS - 2) 
	{ // down arrow
		playSound(1, 1);
		CurPos.Y++;
	}
	else if (input == 75 && CurPos.X != 1) 
	{ // left arrow
		playSound(1, 1);
		CurPos.X--;
	}
	else if (input == 77 && CurPos.X < COLS - 2) 
	{ // right arrow
		playSound(1, 1);
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
			  _______________n_n_
		 _ ,-'                   \_
		(_/                    '_'o\
		  |                    (__) )
		  \    |________|   |___,.-'
		   |   |_|______|   |n_n_
		 _ \___/        \___/    \_
		(_ d888          8888  @ @.\
		   Y888          Y88P    -- )
		   '888b_________d88b___,.-'
			Y888_|_______8888n_n_
		  __"YP"         "YP"    \_
		 (_/                   ' 'o\
		   |                     -- )
		   \    |_______|   |___,.-'
			|   | |     |   | |
			\___/-'     \___/-'

)";
}

void generateBoard(board& curboard, int ROWS, int COLS)
{
	int random1, random2, len = 0;
	char temp[100] = { 0 };
	// gán tất cả phần tử trong mảng curboard[][] = '0'
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int k = 1; k < COLS - 1; k++)
		{
			curboard[i][k].box[2][4] = '0';
		}
	}
	//gắn các kí tự ngẫu nhiên vào 1 nửa bảng và vào mảng tạm temp[]
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int k = 1; k < (COLS / 2); k++)
		{
			//tạo ngẫu nhiên 1 kí tự in hoa trong bảng chữ cái tiếng Anh 26 chữ
			char store = char(rand() % 15 + 65);
			//lưu kí tự dc tạo ngẫu nhiên ở trên vào mảng curboard[][]
			curboard[i][k].box[2][4] = store;
			curboard[i][k].key = store;
			//lưu các kí tự ngẫu nhiên ở trên vào mảng tạm temp[]
			temp[len] = store;
			len++;
		}
	}
	//lưu các kí tự ở trong mảng tạm temp[] vào các ô trống ngẫu nhiên của mảng curboard[][](nửa bảng còn lại)
	for (int i = 0; i < len; i++)
	{
		//vòng lặp do while để tạo ngẫu nhiên dc địa chỉ của 1 ô trống
		do {
			random1 = rand() % (ROWS - 2) + 1;
			random2 = rand() % (COLS - 2) + 1;
			//KeyinBox chỉ tới giá trị hiện tại có trong ô của mảng curboard[][], coi struct board ở trong file Struct.h để hiểu thêm
		} while (curboard[random1][random2].KeyinBox() != '0'); 
		//lưu giá trị của temp[i] vào ô trống có địa chỉ ngẫu nhiên dc tạo ra ở trên 
		curboard[random1][random2].box[2][4] = temp[i];
		curboard[random1][random2].key = temp[i];
	}
}
 
void StandardMode1(Player& curplayer, int ROWS, int COLS, int Continue)
{
	int enterTime = -1; //so lan an enter
	int emptycell = 0; //không tính các ô trống ở viền
	char input = '0';
	int score = 0;
	int i = 1;//turn on/off music
	int savegame = 0; //CHƯA XỬ LÝ BIẾN NÀY

	COORD curpos{ ROWS/2 - 1, COLS/2 };//vị trí của con trỏ trên bảng
	COORD selpos[2]{ -1,-1};//vị trí của 2 con trỏ được chọn để nối với nhau
	COORD helppos[2]{ -1,-1, -1, -1 }; //vị trí của 2 ô được gợi ý 
	COORD temppos[2]{ -1,-1,-1,-1 };
	board newboard = initialBoard(ROWS, COLS);

	system("CLS");
	//initial a board
	drawRectangle(8, 4, 10 * (COLS - 2) + 3, 2 + 5 * (ROWS - 2), WHITE);
	gameBackground(0, 6);
	drawSubTable(86, 5, 20, 3, score);//cập nhật điểm
	drawNotiTable(86, 21, 20, 3, " ", "  HOPE YOU HAVE FUN :3", " ");//cập nhật các thông báo ở bảng noti
	if (Continue == 0) // new game
	{
		generateBoard(newboard, ROWS, COLS);
		drawBoardAtStart(newboard, ROWS, COLS);
		
	}
	else //continue
	{
		stateRead(newboard, curpos, COLS, ROWS, curplayer.state[(ROWS == 6) ? 0 : 1]);
		score = curplayer.state[(ROWS == 6) ? 0 : 1].CurrentScore;
		drawTable(curpos, helppos, newboard, ROWS, COLS);
		int n = 0;
		while (curplayer.state[(ROWS == 6) ? 0 : 1].board[n] != NULL)
		if(curplayer.state[(ROWS == 6) ? 0 : 1].board[n++]=='0')
			emptycell++;
	}
	playSound(3, 1);
	//move cursor in the board
	while (emptycell < (ROWS - 2) * (COLS - 2))
	{
		fflush(stdin);
		
		if (!helpFunc(newboard, ROWS, temppos[0], temppos[1])) //check xem có bị kẹt đường hay không, nếu có thì tráo lại bảng giữ nguyên vị trí
		{
			shuffle2(newboard, ROWS);
			drawTable(curpos, helppos, newboard, ROWS, COLS);
		}

		drawSubTable(86, 5, 20, 3, score);//cập nhật điểm
		drawTable(curpos, helppos, newboard, ROWS, COLS);
		input = _getch();//nhận lệnh từ bàn phím
		enterTime += selectCell(input, curpos, newboard);//đếm số lần enter
		// turn on/off music
		if (input == 'o' || input == 'O')//xu ly khi an bat/ tat nhac
		{
			i = i*-1;
			playSound(3, i);
			string t = (i == 1) ? "    MUSIC IS NOW ON" : "    MUSIC IS NOW OFF";
			drawNotiTable(86, 21, 20, 3, " ", t, " ");
		}
		else if (input == 72 || input == 75 || input == 77 || input == 80) //xu ly khi an phim mui ten de di chuyen
		{
			getPosition(input, curpos, ROWS, COLS);
			string line1;
			string line2;
			line1 = " YOU ARE AT ";
			line2 = "CELL[]|[]";
			line2.insert(5, to_string(curpos.Y));
			line2.insert(9, to_string(curpos.X));
			drawNotiTable(86, 21, 20, 3, " ", line1 + line2, " ");
		}//
		else if (enterTime == 0 && newboard[curpos.Y][curpos.X].isSelected == 1)//xu ly khi an enter lan 1
		{
			if(input=='\r')
			playSound(2, 1);
			selpos[0].Y = curpos.Y; 
			selpos[0].X = curpos.X; 
			string line1;
			string line2;
			line1 = "   YOU ARE SELECTING";
			line2 = "CELL[][]";
			line2.insert(5, to_string(curpos.Y));
			line2.insert(8, to_string(curpos.X));
			line2 = "      " + line2;
			drawNotiTable(86, 21, 20, 3, line1 ,line2, " ");
		}
		else if (enterTime == 1) //xu ly khi an enter lan 2
		{
			selpos[1].Y = curpos.Y;
			selpos[1].X = curpos.X;
			enterTime = -1;
			if ( newboard[selpos[0].Y][selpos[0].X].KeyinBox() == newboard[selpos[1].Y][selpos[1].X].KeyinBox() && checkAndDraw(newboard, selpos[0], selpos[1], ROWS, 14) != 0)
			{
				playSound(2, 1);
				
				int getscore = checkAndDraw(newboard, selpos[0], selpos[1], ROWS, 14);
				Sleep(700);
				checkAndDraw(newboard, selpos[0], selpos[1], ROWS, 0);
				drawRectangle(8, 4, 10 * (COLS - 2) + 3, 2 + 5 * (ROWS - 2), WHITE);
				newboard[selpos[0].Y][selpos[0].X].deBox();
				newboard[selpos[1].Y][selpos[1].X].deBox();
				string line1 = "        GREAT!!!";
				string line2 = "YOU HAVE GOT " + to_string(getscore) +  " POINTS !!!";
				drawNotiTable(86, 21, 20, 3, line1, line2, " ");
				emptycell += 2;
				score += getscore; 
			}
			else
			{
				playSound(6, 1);
				newboard[selpos[0].Y][selpos[0].X].select();
				newboard[selpos[1].Y][selpos[1].X].select();
				enterTime = -1;
				string line1 = " OOPS! INVALID MATCHING";
				string line2 = "   PLEASE TRY AGAIN ^^";
				drawNotiTable(86, 21, 20, 3, line1, line2, " ");//cập nhật các thông báo ở bảng noti
			}
		}
		else if (input == 'q' || input =='Q') //xu ly khi chon chuc nang move suggestion
		{
			playSound(1, 1);
			helpFunc(newboard, ROWS, helppos[0], helppos[1]);
			drawTable(curpos, helppos, newboard, ROWS, COLS);
			Sleep(500);
			//reset suggestion position
			temppos[0] = helppos[0];
			temppos[1] = helppos[1];
			helppos[0] = { -1, -1 };
			helppos[1] = { -1, -1 };
			drawTable(curpos, helppos, newboard, ROWS, COLS);
			string line1;
			string line2;
			string line3;
			line1 = " USING MOVE SUGGESTION";
			line2 = " [][]";
			line2.insert(2, to_string(temppos[0].Y));
			line2.insert(5, to_string(temppos[0].X));
			line3 = "[][]";
			line3.insert(1, to_string(temppos[1].Y));
			line3.insert(4, to_string(temppos[1].X));
			line2 += " MATCHES " + line3;
			drawNotiTable(86, 21, 20, 3, line1, line2, " -3 POINTS");//cập nhật các thông báo ở bảng noti
			score -= 3;
		}
		else if (input == 's' || input == 'S')
		{
			shuffle2(newboard, ROWS);
			string line1 = " BOARD WAS SHUFFLED";
			string line2 = "      -1 POINTS ";
			score -= 1;
			drawNotiTable(86, 21, 20, 3, line1, line2, " ");
			Sleep(1000);
		}
		else if (input == 'f' || input == 'F')
		{
			stateSave(newboard, curpos, COLS, ROWS, curplayer.state[(ROWS == 6) ? 0 : 1]);
			curplayer.state[(ROWS == 6) ? 0 : 1].CurrentScore = score;
			string t =  "   SAVE SUCCESSFULLY";
			drawNotiTable(86, 21, 20, 3, " ", t, " ");
			Sleep(2000);
			savegame = 1;
			break;
		}
		drawTable(curpos, helppos, newboard, ROWS, COLS);
	}
	playSound(3, -1);
	if (savegame == 0)
	{
		playSound(7, 1);
		curpos.Y = 0;
		curpos.X = 0;
		drawTable(curpos, helppos, newboard, ROWS, COLS);
		for (int j = 0; j < 5; j++)
		{
			SetConsoleTextAttribute(hConsole, 10 + j);
			gotoxy(0, 15);
			cout << R"(
	 __     __ ____   _    _  __          __ ____   _   _   _  _  
	 \ \   / // __ \ | |  | | \ \        / // __ \ | \ | | | || |
	  \ \_/ /| |  | || |  | |  \ \  /\  / /| |  | ||  \| | | || |
	   \   / | |  | || |  | |   \ \/  \/ / | |  | || . ` | | || |
	    | |  | |__| || |__| |    \  /\  /  | |__| || |\  | |_||_|
	    |_|   \____/  \____/      \/  \/    \____/ |_| \_| (_)(_))";
			if(ROWS!=6)drawRectangle(8, 4, 10 * (COLS - 2) + 3, 2 + 5 * (ROWS - 2), 10 + j);
			Sleep(1000);
		}
		;
		curplayer.state[(ROWS == 6) ? 0 : 1].CurrentScore = 0;
		curplayer.state[(ROWS == 6) ? 0 : 1].board[0] = NULL; // empty the save state
		Sleep(1000);
		releaseBoard(newboard, ROWS, COLS);
	}
	if(score >= curplayer.record.points)
	curplayer.recordSave(score);
}
