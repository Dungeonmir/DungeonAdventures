#pragma once
#include <libtcod.hpp>
#include "Renderer.h"
class Actor {
public:
	std::string name;
	int x, y; // actor position
	char ch;  // character symbol
	int getHP();
	int getMaxHP();
	int getGold();
	void setGold(int Gold_p);
	void setHP(int HP_p);
	int moveOrAttack(int x, int y);
	TCOD_color_t* color;
	void update();
	Actor(int x, int y, char ch,std::string name, int maxHP, TCOD_color_t* color); // constructor
	void render(RenderWindow* console) const;
private:
	int HP; // Health points
	int maxHP;
	int Gold;
};
