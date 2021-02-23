#include "Engine.h"
Engine engine;
Engine::Engine() {
    gameState = START;
    int consoleX = 80;
    int consoleY = 45;
    interfaceIndent = 10;
    console = new RenderWindow;
    console->init(consoleX, consoleY);
    map = new Map(consoleX - interfaceIndent, consoleY);
    TCOD_color_t* hero_color = new TCOD_color_t{ 100, 0, 100 };
    std::string player_name= "Player";
    hero = new Hero(map->getHeroX(), map->getHeroY(), 'H',player_name, hero_color, 10,0.5f, 0, 0);
    interface = new Interface;
    shader = new Shader;
    hero_light_id = shader->addLight(hero->x, hero->y, FOV_RADIUS, TCOD_white);
    shader->init(map->getMap());
    map->handOutRandomGold();
    
    if (enableGammaCorrection) {
        for (int i = 0; i < 256; i++) {
            float v = i / 255.0f;
            float correctedV = powf(v, GAMMA);
            gammaLookup[i] = (int)(correctedV * 255);
        }
    }
    else {
        for (int i = 0; i < 256; i++) {
            gammaLookup[i] = i;
        }
    }

}
Engine::~Engine() {
    actors.clearAndDelete();
    engine.map->~Map();
}
void Engine::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_KEYDOWN)
        {
            int dx = 0, dy = 0;
            switch (event.key.keysym.sym) {
            case SDLK_w:
                dy = -1;
                break;
            case SDLK_a:
                dx = -1;
                break;
            case SDLK_s:
                dy = 1;
                break;
            case SDLK_d:
                dx = 1;
                break;
            case SDLK_h:
                hero->setGold(hero->getGold() + 1);
                break;
            case SDLK_ESCAPE:
                
                engine.~Engine();
                console->~RenderWindow();
                exit(0);
            }
            
            if (dx != 0 || dy != 0)
            {
                gameState = UPDATE;
                if (hero->moveOrAttack(hero->x + dx, hero->y + dy)) {
                    shader->updateLight(hero_light_id, hero->x, hero->y, FOV_RADIUS, TCOD_white);
                }
            }
        }

        if (gameState == UPDATE) {
            for (Actor** iterator = actors.begin(); iterator != actors.end();
                iterator++) {
                Actor* actor = *iterator;
                    actor->update();

            }
        }




        console->clear();
        map->render(console);
        shader->computeLight();
        hero->render(console);
        interface->render(console);
        console->update();

    }
    gameState = IDLE;
}
void Engine::render() {
    
    console->clear();
    shader->computeLight();
    map->render(console);
    
    }