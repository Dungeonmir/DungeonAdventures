#include "Actor.h"
#include "Engine.h"

Actor::Actor(int x, int y, char ch, std::string name,float maxHP, float attack, TCOD_color_t* color) 
	: x(x), y(y),  ch(ch),name(name), color(color), Attack(attack),maxHP(maxHP), HP(maxHP){
	Gold = 0;
}

void Actor::render(RenderWindow* console) const {
	console->print(x, y, ch, color);
}
void Actor::increaseAttack(float addition)
{
	Attack += addition;
}
void Actor::die(Actor* actor) {
	actor->block = false;
	actor->ch = 'X';
}
float Actor::getHP()
{
	return HP;
}
float Actor::getMaxHP()
{
	return maxHP;
}
float Actor::getAttack()
{
	return Attack;
}
int Actor::getGold()
{
	return Gold;
}
void Actor::takeDamage(Actor* target, float damage)
{
	target->HP -= damage;
	printf("Damage is: %f\n", damage);
	printf("Monster hp: %f\n",target->HP);
	if (target->HP <=0)
	{
		engine.hero->setGold(engine.hero->getGold()+ target->Gold);
		engine.hero->increaseAttack(target->Attack/4);
		die(target);
	}
}
void Actor::setGold(int Gold_p)
{
	Gold = Gold_p;
}
void Actor::setHP(int HP_p)
{
	HP = HP_p;
}

int Actor::moveOrAttack(int x, int y)
{
	if ( engine.map->isWall(x,y) ) return false;
	for (Actor **iterator=engine.actors.begin();
		iterator != engine.actors.end(); iterator++) {
		Actor *actor=*iterator;
		if ( actor->x == x && actor->y ==y and actor->block == true) {
			takeDamage(actor, engine.hero->getAttack());
			return false;
		}
	}
	this->x=x;
	this->y=y;
	return true;
}

void Actor::update() {
	TCOD_color_t light = engine.shader->getLightColor(this->x, this->y);
	if (light.r>0)
	{
		//go to hero and beat him.
	}
}