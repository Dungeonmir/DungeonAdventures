#include "Actor.h"

Actor::Actor(int x, int y, char ch) 
	: x(x), y(y),  ch(ch), color(color) {
}

void Actor::render(RenderWindow* console) const {
	
	console->print(x, y, ch);
	//need to add character color
}
int Actor::getHP()
{
	return HP;
}