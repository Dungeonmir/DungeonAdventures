#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;


bool stop = false;
char hero_char = 254;
int hero_x = 75;
int hero_y = 25;


void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);



	//Изменение размера консоли
	system("mode con cols=150 lines=50"); 
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);




	//Запрещает выделение
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevConsoleMode = 0;
	GetConsoleMode(hConsole, &prevConsoleMode);
	SetConsoleMode(hConsole, prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE);


	//Запрещает изменение размера окна
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}


void goto_x_y(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void hero_move(char key)
{
	switch (key)
	{
	case 'w':
	case 'W':
		printf("\b");
		printf(" ");
		hero_y--;
		goto_x_y(hero_x, hero_y);

		break;

	case 'a':
	case 'A':
		printf("\b");
		printf(" ");
		hero_x -= 2;
		goto_x_y(hero_x, hero_y);

		break;

	case 's':
	case 'S':
		printf("\b");
		printf(" ");
		hero_y++;
		goto_x_y(hero_x, hero_y);


		break;
	case 'd':
	case 'D':
		printf("\b");
		printf(" ");
		hero_x += 2;
		goto_x_y(hero_x, hero_y);

		break;

	case 27: stop = true;

		break;
	}
}
void step() {
	printf("\b");
	printf("%c", hero_char);
}
int main()
{
	system("color 30");
	hideCursor();
	goto_x_y(hero_x, hero_y);
	printf("%c", hero_char);


	char key;
	while (stop == false)
	{
		if (_kbhit())
		{
			key = _getch();
			hero_move(key);
		}
		step();
	}
	return 0;
}

