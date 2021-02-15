#define NOMINMAX
#include <libtcod.hpp>
#include "soloud.h"
#include "soloud_thread.h"
#include "soloud_wav.h"
#include "Map.h"


int main()
{
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
			playery--; break;
		case TCODK_DOWN: 
			playery++; break;
		case TCODK_LEFT: 
			playerx--; break;
		case TCODK_RIGHT: 
			playerx++; break;
		default:break;
		}
		TCODConsole::root->clear();
		TCODConsole::root->putChar(playerx, playery, '@');
		TCODConsole::flush();
	}
	
	soloud.deinit();
	return 0;
}

