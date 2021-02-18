#pragma once
#include "libtcod.hpp"
#include "Renderer.h"
#include "Actor.h"

class Hero : public Actor {
public:
	int getHP();
	int getEXP();
	int getMP();
	void setHP(int HP_p);
	void setEXP(int EXP_p);
	void setMP(int MP_p);
private:
	int HP; // Health points
	int EXP; //Experience
	int MP; //Magic points
};