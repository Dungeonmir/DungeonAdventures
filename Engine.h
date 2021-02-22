#pragma once
#include <libtcod.h>

#include "Actor.h"
#include "Engine.h"
#include "Map.h" // Заголовочный файл Карты
#include "Renderer.h"
#include "Interface.h"
#include "Hero.h"
#include "Shader.h"
class RenderWindow;
class Interface;
class Map;
class Engine {
public:
	enum GameState
	{
		START, // start of the game
		IDLE, // Nothing changed
		UPDATE, // Updates monsters position
		VICTORY, // You succesfully beat the monster
		DEATH // YOU DIED!
	};
	GameState gameState;
	TCODList<Actor*> actors;
	RenderWindow* console;
	Interface* interface;
	Map* map;
	Hero* hero;
	Shader* shader;
	int hero_light_id;
	Engine();
	~Engine();
	void update();
	void render();

	bool enableGammaCorrection = true;
	int gammaLookup[256];
	#define GAMMA (1 / 2.2f)
};

extern Engine engine;