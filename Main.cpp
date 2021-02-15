#define NOMINMAX
#include <libtcod.hpp>
#include "soloud.h" // Отвечает за музыку
#include "soloud_thread.h"
#include "soloud_wav.h" 
#include "Map.h" // Заголовочный файл Карты
#include <stdlib.h> // Для ESC
#include <iostream>

int main() {
    SoLoud::Soloud soloud;  // SoLoud engine core
    SoLoud::Wav gWave;      // One wave file
    soloud.init();
    gWave.load("audio/darlsouls.ogg"); // Load a wave
    soloud.play(gWave); // Play the wave

    int playerx = 40, playery = 25;
    TCODConsole::initRoot(80, 50, "DyabloLR", false);
    Map level1(80, 50);
    while (!TCODConsole::isWindowClosed()) {

    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch (key.vk) {
        case TCODK_UP: 
            if (!level1.isWall(playerx, playery - 1))
            {
                playery--;
            }
            break;
        case TCODK_DOWN:
            if (!level1.isWall(playerx, playery + 1))
            {
                playery++;
            }
            break;
        case TCODK_LEFT:
            if (!level1.isWall(playerx - 1,playery))
            {
                playerx--;
            }
               
            break;
        case TCODK_RIGHT:
            if (!level1.isWall(playerx + 1, playery))
            {
                playerx++;
            }
            break;
        case TCODK_ESCAPE:
            exit(0);
            default:break;
            }
            TCODConsole::root->clear();
            level1.render();
            
            TCODConsole::root->putChar(playerx, playery, '@');

            TCODConsole::flush();
        }
        return 0;
    }

