#include "Interface.h"

void Interface::render(RenderWindow* console, int maxHP, int HP, int MP, int EXP, int Gold)
{
	TCOD_color_t* health_color = new TCOD_color_t{ 220, 0, 0 };
	TCOD_color_t* unhealth_color = new TCOD_color_t{20, 0, 0 };
	TCOD_color_t* dynamic_color = new TCOD_color_t{ 10, 0, 0 }; // colors

	int x = console->getConsoleX() - 3;
	int y = console->getConsoleY() - 1; // handy variables to arrange items of interface
	for (int  i = maxHP; i > 0; i--)
	{
		unhealth_color->r = unhealth_color->r + dynamic_color->r;
		console->print(x, y - i, std::string("  "), nullptr, unhealth_color);
	}
	for (int i = HP; i > 0; i--)
	{
		health_color->r = health_color ->r - dynamic_color->r; // changing the color 
		console->print(x, y-i, std::string("  "), nullptr, health_color);
	}
	console->print(x, y, std::string("HP")); // prints HP to show that it is health bar upper in column
	console->print(x, y/2, std::to_string(Gold)+"$"); //prints gold
}
