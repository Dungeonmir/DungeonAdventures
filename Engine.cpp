#include "Engine.h"


Engine::Engine() {
    int consoleX = 60;
    int consoleY = 40;
    console = new RenderWindow;
    console->init(consoleX, consoleY);
    map = new Map(consoleX - 4, consoleY);
    TCOD_color_t* hero_color = new TCOD_color_t{ 100, 0, 100 };
    hero = new Hero(map->getHeroX(), map->getHeroY(), 'H', hero_color, 10, 0, 0);
    interface = new Interface;
}
Engine::~Engine() {
    actors.clearAndDelete();
    delete map;
}
void Engine::update() {
    bool computeFov = true;
    SDL_Event event;
    while (!TCODConsole::isWindowClosed()) {


        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    computeFov = true;
                    if (map->isWall(hero->x, hero->y - 1))
                    {

                    }
                    else hero->y--;

                    break;
                case SDLK_a:
                    computeFov = true;
                    if (map->isWall(hero->x - 1, hero->y))
                    {

                    }
                    else hero->x--;

                    break;
                case SDLK_s:
                    computeFov = true;
                    if (map->isWall(hero->x, hero->y + 1))
                    {

                    }
                    else hero->y++;

                    break;
                case SDLK_d:
                    computeFov = true;
                    if (map->isWall(hero->x + 1, hero->y))
                    {

                    }
                    else hero->x++;

                    break;
                case SDLK_h:
                    hero->setHP(hero->getHP() - 1);
                    break;
                case SDLK_ESCAPE:
                    console->~RenderWindow();
                }
                if (computeFov) {
                    map->computeFov(hero->x, hero->y);
                    computeFov = false;
                }
            }


        }

        console->clear();
        map->render(console);

        hero->render(console);

        console->print(0, 0, "Work in progress...");
        interface->render(console, hero->getMaxHP(), hero->getHP(), hero->getMP(), hero->getEXP(), hero->getGold());
        console->update();

    }
}
void Engine::render() {
    console->clear();
    map->render(console);
    for (Actor** iterator = actors.begin(); iterator != actors.end(); iterator++) 
    {
        (*iterator)->render(console);
    }
    }