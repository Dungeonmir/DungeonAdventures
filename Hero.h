#pragma once
#include "libtcod.hpp"
#include "Renderer.h"
#include "Actor.h"

class Hero : public Actor {
public:
	int getEXP();
	int getMP();
	void setEXP(int EXP_p);
	void setMP(int MP_p);
private:
	int EXP; //Experience
	int MP; //Magic points
};