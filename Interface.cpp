#include "Interface.h"

void Interface::render(RenderWindow* console, int maxHP, int HP, int MP, int EXP)
{
	TCOD_color_t* health_color = new TCOD_color_t{ 200, 0, 0 };
	TCOD_color_t* unhealth_color = new TCOD_color_t{ 0, 0, 0 };
	TCOD_color_t* dynamic_color = new TCOD_color_t{ 10, 0, 0 };
	
	int y = console->getConsoleY() - 1;
	for (int  i = maxHP; i > 0; i--)
	{
		unhealth_color->r = unhealth_color->r + dynamic_color->r;
		console->print(1, y - i, std::string("  "), nullptr, unhealth_color);
	}
	for (int i = HP; i > 0; i--)
	{
		health_color->r = health_color ->r - dynamic_color->r;
		console->print(1, y-i, std::string("  "), nullptr, health_color);
	}

}
