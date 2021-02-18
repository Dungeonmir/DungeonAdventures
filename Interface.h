#pragma once
#include "libtcod.hpp"
#include "Renderer.h"

class Interface {
public:
	void render(RenderWindow* console, int maxHP, int HP, int MP, int EXP);
private:
};