#include "Engine.h"

Engine engine;
Engine::Engine() {
    int consoleX = 60;
    int consoleY = 40;
    console = new RenderWindow;
    console->init(consoleX, consoleY);
    map = new Map(consoleX - 4, consoleY);
    TCOD_color_t* hero_color = new TCOD_color_t{ 100, 0, 100 };
    std::string player_name= "Player";
    hero = new Hero(map->getHeroX(), map->getHeroY(), 'H',player_name, hero_color, 10, 0, 0);
    interface = new Interface;
    shader = new Shader;
    hero_light_id = shader->addLight(hero->x, hero->y, FOV_RADIUS, TCOD_white);
    shader->init(map->getMap());
    
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
    delete map;
}
void Engine::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    shader->updateLight(hero_light_id, hero->x, hero->y, FOV_RADIUS, TCOD_white);
                    if (map->isWall(hero->x, hero->y - 1))
                    {

                    }
                    else hero->y--;

                    break;
                case SDLK_a:
                    shader->updateLight(hero_light_id, hero->x, hero->y, FOV_RADIUS, TCOD_white);
                    if (map->isWall(hero->x - 1, hero->y))
                    {

                    }
                    else hero->x--;

                    break;
                case SDLK_s:
                    shader->updateLight(hero_light_id, hero->x, hero->y, FOV_RADIUS, TCOD_white);
                    if (map->isWall(hero->x, hero->y + 1))
                    {

                    }
                    else hero->y++;

                    break;
                case SDLK_d:
                    shader->updateLight(hero_light_id, hero->x, hero->y, FOV_RADIUS, TCOD_white);
                    if (map->isWall(hero->x + 1, hero->y))
                    {

                    }
                    else hero->x++;

                    break;
                case SDLK_h:
                    hero->setGold(hero->getGold() + 1);
                    break;
                case SDLK_ESCAPE:
                    console->~RenderWindow();
                }
               
            }


        

        console->clear();
        map->render(console);
        shader->computeLight();
        hero->render(console);
        interface->render(console, hero->getMaxHP(), hero->getHP(), hero->getMP(), hero->getEXP(), hero->getGold());
        console->update();

    }
}
void Engine::render() {
    
    console->clear();
    shader->computeLight();
    map->render(console);
    
    }