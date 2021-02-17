#include "Renderer.h"


void RenderWindow::init(int argc, char* argv[])
{
    TCOD_tileset_load_truetype_("font/RobotoSlab-Medium.ttf", 20, 20);
    console = tcod::new_console(30, 20);
    TCOD_ContextParams params = {}; //Struct for creating context
    params.tcod_version = TCOD_COMPILEDVERSION; // Required 
    params.columns = console->w; //Set console window size = console size
    params.rows = console->h;
    params.renderer_type = TCOD_RENDERER_SDL2;
    params.vsync = true;
    params.argc = argc; // This allows some user-control of the context.
    params.argv = argv;
    context = tcod::new_context(params);
}


    