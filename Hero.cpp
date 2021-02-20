#include "Hero.h"

Hero::Hero(int x, int y, char ch,std::string name, TCOD_color_t* color, int HP, int MP_p, int EXP_p)
	:Actor(x, y, ch, name, HP, color) 
{
	MP = MP_p;
	EXP = EXP_p;

	
}
int Hero::getEXP()
{
	return EXP;
}

int Hero::getMP()
{
	return MP;
}

void Hero::setEXP(int EXP_p)
{
	EXP = EXP_p;
}

void Hero::setMP(int MP_p)
{
	MP = MP_p;
}
