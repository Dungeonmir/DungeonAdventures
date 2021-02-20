#pragma once
#include <libtcod.h>
#include "Actor.h"
#include "Engine.h"
#include "Map.h" // Заголовочный файл Карты
#include "Renderer.h"
#include "Interface.h"
#include "Hero.h"
class RenderWindow;
class Interface;
class Map;
class Engine {
public:
	TCODList<Actor*> actors;
	RenderWindow* console;
	Interface* interface;
	Map* map;
	Hero* hero;
	Engine();
	~Engine();
	void update();
	void render();
};

extern Engine engine;