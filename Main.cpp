#define NOMINMAX
#include <libtcod.hpp>
#include <stdlib.h> // Для ESC
#include <iostream>
#include <SDL.h> //SDL2 renderer
#undef main // !DANGER SDL.h has conflict with SDL_main.h!

#include "soloud.h" // Отвечает за музыку
#include "soloud_thread.h"
#include "soloud_wav.h" 
#include "Map.h" // Заголовочный файл Карты

int main(int argc, char* argv[]) {
    SoLoud::Soloud soloud;  // SoLoud engine core
    SoLoud::Wav gWave;      // One wave file
    soloud.init();
    gWave.load("audio/darlsouls.ogg"); // Load a wave
    soloud.play(gWave); // Play the wave
    
    TCOD_tileset_load_truetype_("RobotoSlab-Medium.ttf", 32, 32);
    tcod::ConsolePtr console = tcod::new_console(30, 20);
    TCOD_ContextParams params = {}; //Struct for creating context
    params.tcod_version = TCOD_COMPILEDVERSION; // Required 
    params.columns = console->w; //Set console window size = console size
    params.rows = console->h;
    params.renderer_type = TCOD_RENDERER_SDL2;
    params.vsync = true;
    params.argc = argc; // This allows some user-control of the context.
    params.argv = argv;
    tcod::ContextPtr context = tcod::new_context(params);
    

        Map level1(80, 50);
        while (!TCODConsole::isWindowClosed()) {

            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                switch (event.key.keysym.sym) {
                case SDL_QUIT:
                case SDLK_ESCAPE:
                    gWave.~Wav();
                    soloud.deinit();
                    console.release();
                    return 0;
                }
            }

            TCOD_console_clear(console.get());
            level1.render();
            
            const TCOD_color_t back = {100, 50, 60};
            const TCOD_color_t* backi = &back;
            
            tcod::print(*console, 0, 0, "Line", nullptr, nullptr, TCOD_BKGND_NONE, TCOD_LEFT);
            
            context->present(*console); // Updates the visible display.
            
        }
        soloud.deinit();
        return 0;
}
