#include "Actor.h"

Actor::Actor(int x, int y, char ch,int maxHP, TCOD_color_t* color) 
	: x(x), y(y),  ch(ch), color(color), maxHP(maxHP), HP(maxHP){
	
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
void Actor::setHP(int HP_p)
{
	HP = HP_p;
}