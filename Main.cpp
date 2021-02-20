#define NOMINMAX

#include <stdlib.h> // Для ESC
#include <iostream>
#include <libtcod.hpp>
#include <SDL.h> //SDL2 renderer
#undef main // !DANGER SDL.h has conflict with SDL_main.h!
#include "Engine.h"


int main() {
    Engine engine;
    engine.update();
    engine.render();
    return 0;
}
