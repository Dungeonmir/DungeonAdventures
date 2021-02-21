#include "Actor.h"

Actor::Actor(int x, int y, char ch, std::string name,int maxHP, TCOD_color_t* color) 
	: x(x), y(y),  ch(ch),name(name), color(color), maxHP(maxHP), HP(maxHP){
	Gold = 0;
}

void Actor::render(RenderWindow* console) const {
	
	console->print(x, y, ch, color);
	//need to add character color
}
int Actor::getHP()
{
	return HP;
}
int Actor::getMaxHP()
{
	return maxHP;
}
int Actor::getGold()
{
	return Gold;
}
void Actor::setGold(int Gold_p)
{
	Gold = Gold_p;
}
void Actor::setHP(int HP_p)
{
	HP = HP_p;
}
