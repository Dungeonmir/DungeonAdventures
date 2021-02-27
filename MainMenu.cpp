#include "MainMenu.h"
#include "Engine.h"
#include <iostream>

void MainMenu()
{
	int menu = -1;
	int x = engine.console->getConsoleX();
	int y = engine.console->getConsoleY();
	std::string cont = "Welcome to Dungeon Adventures!";

	int xx = x / 2 - cont.length()/2;
	int yy = y / 2;
	TCOD_color_t* menu_col = new TCOD_color_t{ 255,255,255 };
	TCOD_color_t* menu_col_fon = new TCOD_color_t{ 0,0,0 };
	engine.console->print(xx, yy, cont, menu_col_fon, menu_col);
	engine.console->update();
	engine.console->clear();
	SDL_Event event;
	while (menu != 0)
	{
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN)
		{
			menu = 0;
		}
	}
	}
}