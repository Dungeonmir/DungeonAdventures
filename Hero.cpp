#include "Hero.h"

int Hero::getHP()
{
	return HP;
}

int Hero::getEXP()
{
	return EXP;
}

int Hero::getMP()
{
	return MP;
}

void Hero::setHP(int HP_p)
{
	HP = HP_p;
}

void Hero::setEXP(int EXP_p)
{
	EXP = EXP_p;
}

void Hero::setMP(int MP_p)
{
	MP = MP_p;
}
