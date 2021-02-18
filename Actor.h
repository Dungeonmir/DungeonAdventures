#pragma once
#include <libtcod.hpp>
#include "Renderer.h"
class Actor {
public:
	int x, y; // actor position
	char ch;  // character symbol
	int getHP();
	int getMaxHP();
	void setHP(int HP_p);
	TCOD_color_t* color;

	Actor(int x, int y, char ch, int maxHP, TCOD_color_t* color); // constructor
	void render(RenderWindow* console) const;
private:
	int HP; // Health points
	int maxHP;
};
