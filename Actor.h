#pragma once
#include <libtcod.hpp>
class Actor {
public:
	int x, y; // actor position
	int ch;  // character symbol
	TCODColor color;

	Actor(int x, int y, int ch, const TCODColor& col); //default constructor
	void render() const;
};
