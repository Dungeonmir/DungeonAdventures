#define NOMINMAX
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <libtcod.hpp>
#include "soloud.h"
#include "soloud_thread.h"
#include "soloud_wav.h"


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
	
	int playerx = 40, playery = 25;
	TCODConsole::initRoot(80, 50, "libtcod C++ tutorial", false);
	while (!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		switch (key.vk) {
		case TCODK_UP: playery--; break;
		case TCODK_DOWN: playery++; break;
		case TCODK_LEFT: playerx--; break;
		case TCODK_RIGHT: playerx++; break;
		default:break;
		}
		TCODConsole::root->clear();
		TCODConsole::root->putChar(playerx, playery, '@');
		TCODConsole::flush();
	}
	
	soloud.deinit();
	return 0;
}

