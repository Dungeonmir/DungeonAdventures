
#include "Interface.h"
#include "Engine.h"
void Interface::render(RenderWindow* console)
{
	//engine.hero->getMP(), engine.hero->getEXP()
	
	TCOD_color_t* health_color = new TCOD_color_t{ 220, 0, 0 };
	TCOD_color_t* unhealth_color = new TCOD_color_t{20, 0, 0 };
	TCOD_color_t* dynamic_color = new TCOD_color_t{ 10, 0, 0 }; // colors
	int indent = engine.interfaceIndent;
	int x = console->getConsoleX() - indent;
	int y = console->getConsoleY() - 1; // handy variables to arrange items of interface
	for (int  i = engine.hero->getMaxHP(); i > 0; i--)
	{
		unhealth_color->r = unhealth_color->r + dynamic_color->r;
		console->print(x, y - i, std::string("  "), nullptr, unhealth_color);
	}
	for (int i = engine.hero->getHP(); i > 0; i--)
	{
		health_color->r = health_color ->r - dynamic_color->r; // changing the color 
		console->print(x, y-i, std::string("  "), nullptr, health_color);
	}
	std::string hp = std::to_string(engine.hero->getHP());
	hp = hp.substr(0, hp.find(".")+2 );
	std::string maxhp = std::to_string(engine.hero->getMaxHP());
	maxhp = maxhp.substr(0, maxhp.find(".") );
	console->print(x, y, hp + "/" + maxhp); // prints HP to show that it is health bar upper in column
	console->print(x, y/2, std::to_string(engine.hero->getGold())+"$"); //prints gold
	
	std::string atk = std::to_string(engine.hero->getAttack());
	 atk = atk.substr(0, atk.find(".") + 3);
	console->print(x, y / 2+1, atk + " ATK"); //prints hero attack
}
