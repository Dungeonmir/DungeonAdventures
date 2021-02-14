#define NOMINMAX
#include <iostream>
#include <libtcod.hpp>
#include "soloud.h"
#include "soloud_thread.h"
#include "soloud_wav.h"


bool stop = false;
char hero_char = 254;
int hero_x = 75;
int hero_y = 25;


void step() {
	
}
int main()
{
	SoLoud::Soloud soloud;  // SoLoud engine core

	SoLoud::Wav gWave;      // One wave file

	soloud.init();

	gWave.load("audio/darlsouls.ogg"); // Load a wave
	soloud.play(gWave); // Play the wave
	
	int playerx = 40, playery = 25;
	TCODConsole::initRoot(100, 30, "libtcod", false);
	while (!TCODConsole::isWindowClosed()) {
		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		switch (key.vk) {
		case TCODK_UP: playery--; break;
		case TCODK_DOWN: playery++; break;
		case TCODK_LEFT: playerx--; break;
		case TCODK_RIGHT: playerx++; break;
		default:break;
		}
		TCODConsole::root->clear();
		TCODConsole::root->putChar(playerx, playery, '@');
		TCODConsole::flush();
	}
	soloud.deinit();
	return 0;
}

