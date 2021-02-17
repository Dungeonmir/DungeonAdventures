#define NOMINMAX

#include <stdlib.h> // Для ESC
#include <iostream>
#include <libtcod.hpp>
#include <SDL.h> //SDL2 renderer
#undef main // !DANGER SDL.h has conflict with SDL_main.h!


#include "Map.h" // Заголовочный файл Карты
#include "Renderer.h"

int main(int argc, char* argv[]) {
    
    
    RenderWindow console;
    console.init(argc,argv);
    
        Map level1(80, 50);
        while (!TCODConsole::isWindowClosed()) {

            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return 0;
                }
            }

            console.clear();
            level1.render(&console);
            
            
            
            console.print(0, 0, "Here it is. The code ////");
            
            console.update();
            
        }
        return 0;
}
