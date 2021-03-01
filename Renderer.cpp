#include "Renderer.h"


void RenderWindow::init(int x, int y)
{
    consoleX = x;
    consoleY = y;
    TCOD_tileset_load_truetype_("font/font.ttf", 20, 20);
    console = tcod::new_console(x, y);
    TCOD_ContextParams params = {}; //Struct for creating context
    params.tcod_version = TCOD_COMPILEDVERSION; // Required 
    params.columns = console->w; //Set console window size = console size
    params.rows = console->h;
    params.renderer_type = TCOD_RENDERER_SDL2;
    params.vsync = true;
    context = tcod::new_context(params);
}


    