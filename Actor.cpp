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
	printf("%s hp: %f\n",target->name,target->HP);
	if (target->HP <=0 && target->name!="Player")
	{
		engine.hero->setGold(engine.hero->getGold()+ target->Gold);
		engine.hero->increaseAttack(target->Attack/4);
		die(target);
	}
	else if (target->HP <= 0)
	{
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
		if ( actor->x == x && actor->y ==y && actor->block == true) {
			takeDamage(actor, engine.hero->getAttack());
			return false;
		}
		if (engine.hero->x == x && engine.hero->y == y && engine.hero->block ==true && this->block==true && this->name!="Player")
		{
			int dx = x - this->x;
			int dy = y - this->y;
			
			float distance = sqrtf(dx * dx + dy * dy);
			if (distance >= 2)
			{
				dx = (int)(round(dx / distance));
				dy = (int)(round(dy / distance));
			}
			int stepdx = (dx > 0 ? 1 : -1);
			int stepdy = (dy > 0 ? 1 : -1);
			if (engine.map->canWalk(this->x + dx, this->y + dy) and this->x + dx !=x and this->y + dy!=y) {
				this->x += dx;
				this->y += dy;
			}
			else if (engine.map->canWalk(this->x + stepdx, this->y and this->x + dx != x and this->y + dy != y)) {
				this->x += stepdx;
			}
			else if (engine.map->canWalk(this->x, this->y + stepdy and this->x + dx != x and this->y + dy != y)) {
				this->y += stepdy;
			}
			else if (distance<2 and this->HP>0)
			{
				takeDamage(engine.hero, this->Attack);
			}
			
				
			return false;
		}
	}
	if (this->block==true && this->name == "Player")
	{
		this->x = x;
		this->y = y;
		return true;
	}
	
}

void Actor::update() {
	TCOD_color_t light = engine.shader->getLightColor(this->x, this->y);
	if (light.r>30)
	{
		moveOrAttack(engine.hero->x, engine.hero->y);
	}
}