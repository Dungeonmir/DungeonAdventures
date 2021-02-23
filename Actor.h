#pragma once
#include <libtcod.hpp>
#include "Renderer.h"
class Actor {
public:
	std::string name;
	bool block = true;
	int x, y; // actor position
	char ch;  // character symbol
	float getHP();
	float getMaxHP();
	float getAttack();
	int getGold();
	void takeDamage(Actor* target, float damage);
	void setGold(int Gold_p);
	void setHP(int HP_p);
	void die(Actor* actor);
	int moveOrAttack(int x, int y);
	TCOD_color_t* color;
	TCOD_color_t* corpse_col = new TCOD_color_t{ 10, 200, 10 };
	void update();
	Actor(int x, int y, char ch,std::string name, float maxHP, float attack, TCOD_color_t* color); // constructor
	void render(RenderWindow* console) const;
	void increaseAttack(float addition);

private:
	float Attack;
	float HP; // Health points
	float maxHP;
	int Gold;
};
