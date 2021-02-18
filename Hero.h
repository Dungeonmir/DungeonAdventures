#pragma once
#include "libtcod.hpp"
#include "Renderer.h"
#include "Actor.h"

class Hero : public Actor {
public:
	Hero(int x, int y, char ch, TCOD_color_t* color, int HP, int MP, int EXP);
	int getEXP();
	int getMP();
	void setEXP(int EXP_p);
	void setMP(int MP_p);
private:
	int EXP; //Experience
	int MP; //Magic points
};