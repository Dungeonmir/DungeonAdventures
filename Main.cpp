#define NOMINMAX

#include <stdlib.h> // Для ESC
#include <iostream>
#include <libtcod.hpp>
#include <SDL.h> //SDL2 renderer
#undef main // !DANGER SDL.h has conflict with SDL_main.h!


#include "Map.h" // Заголовочный файл Карты
#include "Renderer.h"
#include "Actor.h"
#include "Interface.h"
#include "Hero.h"
int main(int argc, char* argv[]) {
    
    int consoleX = 60;
    int consoleY = 40;
    RenderWindow console;
    console.init(argc,argv, consoleX, consoleY);
    
    Map level1(consoleX-4, consoleY);
    TCOD_color_t* hero_color = new TCOD_color_t{ 200, 200, 0 };
    Hero hero(level1.getHeroX(), level1.getHeroY(), 'H', hero_color,10,0,0);
        
    Interface Interface;
    SDL_Event event;
    while (!TCODConsole::isWindowClosed()) {

        
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    if (level1.isWall(hero.x, hero.y - 1))
                    {

                    }
                    else hero.y--;
                    break;
                case SDLK_a:
                    if (level1.isWall(hero.x - 1, hero.y))
                    {

                    }
                    else hero.x--;
                    break;
                case SDLK_s:
                    if (level1.isWall(hero.x, hero.y + 1))
                    {

                    }
                    else hero.y++;
                    break;
                case SDLK_d:
                    if (level1.isWall(hero.x + 1, hero.y))
                    {

                    }
                    else hero.x++;
                    break;
                case SDLK_h:
                    hero.setHP(hero.getHP() - 1);
                    break;
                case SDLK_ESCAPE:
                    return 0;
                    break;
                }
            }
            
        }

        console.clear();
        level1.render(&console);
        
        hero.render(&console);
        
        console.print(0, 0, "Work in progress...");
        Interface.render(&console,hero.getMaxHP(),hero.getHP(), hero.getMP(), hero.getEXP(), hero.getGold());
        console.update();
        
    }
    return 0;
}
