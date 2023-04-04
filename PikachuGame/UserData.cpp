#define _CRT_SECURE_NO_WARNINGS
#include "UserData.h"

string ReturnToday() {
	const int MAXLEN = 80;
	char s[MAXLEN];
	time_t t = time(0);
	strftime(s, MAXLEN, "%d %m %Y", localtime(&t)); // lu dd mm yyyy vao s
	string today = s;
	return today;
}
void printInforBox(int x, int y)
{
	drawRectangle(x, y, 30, 3, WHITE);
	printText("Enter your username", x+1, y-1, WHITE);
	gotoxy(0, 0);
}

void printPasswordBox(int x, int y, int newplayer)
{
	drawRectangle(x, y, 30, 3, WHITE);
	if (newplayer == -1)
		printText("Create your password", x + 1, y - 1, WHITE);
	else 
		printText("Enter your password", x + 1, y - 1, WHITE);
}

int checkNewPlayer(Player curplayer[100], int n, string inputName)
{
	for (int i = 0; i < n; i++)
	{
		if (inputName == curplayer[i].name)
			return i;
	}
	return -1;
}


int addPlayer(Player playerlist[100],int& n, Player newplayer)
{
	playerlist[n].name = newplayer.name;
	playerlist[n].password = newplayer.password;
	n++;
	return 1;
}


int EnterInfor(Player playerlist[100], int &n, int x, int y)//return the index of a player in playerlist to enter the game
{
	char c;
	Player cur;//current player
	int check;
	ShowCur(1);
	do 
	{
		printInforBox(x, y);
		gotoxy(x + 1, y + 1);
		getline(cin, cur.name);
		check = checkNewPlayer(playerlist, n, cur.name);//if check == -1, we have new player, if != 1, check is the index of one of old players
		if (cur.name.empty())
		{
			printText("username cannot be empty", x, y + 3, LIGHT_RED);
		}
	} while (cur.name.empty());
	printText("username cannot be empty", x, y + 3, BLACK);
	y += 4;
	do
	{
	printPasswordBox(x, y, check);
	gotoxy(x + 1, y + 1); 
	getline(cin, cur.password);
	if (cur.password.empty())
	{
		printText("password cannot be empty", x, y + 3, LIGHT_RED);
	}
	} while (cur.password.empty());
	if (check != -1) //old player
	{
		int checkpass = 0;
		do
		{
			cout << endl;
			
			if ( cur.password == playerlist[check].password)
			{
				break;
			}
			else
			{
				printText("You have entered wrong password, please try again...", x , y + 3, LIGHT_RED);
				Sleep(1000);
			}
			printText("You have entered wrong password, please try again...", x, y + 3, 0);
			printText("                       ", x, y + 1, 0);
			printPasswordBox(x, y, check);
			gotoxy(x + 1, y + 1); 
			getline(cin, cur.password);
		} while (1);
	}
	else //new player
	{
		check = n;
		if(addPlayer(playerlist, n, cur)) printText("Create account successfully, press Enter to continue" , x, y + 3, 14);
		c = _getch();
	}
	ShowCur(0);
	return check;
}

void stateSave(board a, COORD cursor, int columns, int rows, State& s)
{
	int len = 0;
	for (int i = 1; i < columns - 1; i++)
	{
		for (int k = 1; k < rows - 1; k++)
		{
			s.board[len] = a[i][k].KeyinBox();
			len++;
		}
	}
	s.board[len] = '/0';
	s.p_ = cursor.X;
	s.q_ = cursor.Y;
	s.p = rows;
	s.q = columns;
	Beep(500, 1000);
}

void stateRead(board &a, COORD &cursor, int columns, int rows, State& s)
{
	int len = 0;
	cursor.X = s.p_;
	cursor.Y = s.q_;
	rows = s.p;
	columns = s.q;
	for (int i = 1; i < columns - 1; i++)
	{
		for (int k = 1; k < rows - 1; k++)
		{
			a[i][k].box[2][4] = s.board[len];
			a[i][k].key = s.board[len];
			len++;
		}
	}
}

void recordSave(Record& r, int points)
{
	//ref: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
	time_t now = time(0);
	//phải xài biến now vì func localtime yêu cầu 1 con trỏ
	tm* ltm = localtime(&now);

	//gán giá trị
	//tm_year, tm_month, tm_day là biến con của struct tm *localtime(const time_t *time);
	r.date.yy = 1900 + ltm->tm_year; // +1900 vì tm_year cho biết đã bao nhiêu năm từ 1900
	r.date.mm = 1 + ltm->tm_mon; // +1 bởi vì tm_mon cho biết tháng của năm chạy từ 0 đến 11
	r.date.dd = ltm->tm_mday;
	r.points = points;
}

void binaryRead(Player player[], const char* fileName, int n)
{
	fstream myfile;
	myfile.open(fileName, ios::binary | ios::in );
	if (!myfile.is_open())
	{
		system("CLS");
		cout << "Error. File don't exsit..." << endl;
		system("pause");
		return;
	}
	//size* sizeof(Player) là để tính kích thước của mảng struct player, ko thể sử dụng sizeof(player) vì nó sẽ trả ra kích thước của con trỏ
	myfile.write((char*)&player,  n * sizeof(Player));
	myfile.close();
}

void binaryWrite(Player player[], const char* fileName, int n)
{
	//viết tất cả vào file
	fstream myfile;
	myfile.open(fileName, ios::binary | ios::out | ios::trunc);
	if (!myfile.is_open())
	{
		system("CLS");
		cout << "Erorr. File don't exist..." << endl;

		system("pause");
		return;
	}
	myfile.write((char*)&player, n * sizeof(Player));//sizeof dùng để lấy kích thước của struct savefile. Coi ref để hiểu thêm.
	myfile.close();
	return;
}

void swap(Player &a, Player &b) 
{
	Player t = a;
	a = b;
	b = t;
}

// Function to implement Interchange Sort
void sortLeaderboard(Player p[], int amountPlayer) 
{
	for (int i = 0; i < amountPlayer; i++)
	{
		for (int k = i + 1; k < amountPlayer; k++)
		{
			if (p[k].record.points > p[i].record.points)
				swap(p[k], p[i]);
		}
	}
}
