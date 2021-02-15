#define NOMINMAX
#include <libtcod.hpp>
#include "soloud.h" // Отвечает за музыку
#include "soloud_thread.h"
#include "soloud_wav.h" 
#include "Map.h" // Заголовочный файл Карты
#include <stdlib.h> // Для ESC

int main() {
    SoLoud::Soloud soloud;  // SoLoud engine core
    SoLoud::Wav gWave;      // One wave file
    soloud.init();
    gWave.load("audio/darlsouls.ogg"); // Load a wave
    soloud.play(gWave); // Play the wave

    int playerx = 40, playery = 25;
    TCODConsole::initRoot(80, 50, "DyabloLR", false);

    while (!TCODConsole::isWindowClosed()) {
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch (key.vk) {
        case TCODK_UP: 
                playery--; 
            break;
        case TCODK_DOWN:
                playery++; 
            break;
        case TCODK_LEFT: 
                playerx--;
            break;
        case TCODK_RIGHT: 
                playerx++; 
            break;
        case TCODK_ESCAPE:
            exit(0);
            default:break;
            }
            TCODConsole::root->clear();
            TCODConsole::root->putChar(playerx, playery, 109);
            TCODConsole::flush();
        }
        return 0;
    }

