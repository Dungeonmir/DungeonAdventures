#include <iostream>
#include <conio.h>
#include <windows.h>

#include "include/soloud.h"
#include "soloud_thread.h"
#include "soloud_wav.h"
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




	system("mode con cols=150 lines=50"); 
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);




	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevConsoleMode = 0;
	GetConsoleMode(hConsole, &prevConsoleMode);
	SetConsoleMode(hConsole, prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE);


	
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
	SoLoud::Soloud soloud;  // SoLoud engine core

	SoLoud::Wav gWave;      // One wave file

	soloud.init();

	gWave.load("audio/darlsouls.ogg"); // Load a wave
	soloud.play(gWave); // Play the wave
	
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
			soloud.play(gWave);
		}
		step();
	}
	soloud.deinit();
	return 0;
}

