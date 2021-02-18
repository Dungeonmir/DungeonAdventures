#pragma once
#include <libtcod.hpp>
#include "Renderer.h"
class Actor {
public:
	int x, y; // actor position
	char ch;  // character symbol
	int getHP();
	TCODColor color;

	Actor(int x, int y, char ch); // constructor
	void render(RenderWindow* console) const;
private:
	int HP; // Health points
};
