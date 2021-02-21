#pragma once
#include <libtcod.h>

class Shader {
public:
	~Shader();
	void init(TCODMap* map);
	// add new light, returns its id
	int addLight(int x, int y, int radius, const TCOD_color_t& col);
	// update the light with id
	void updateLight(int id, int x, int y, int radius, const TCOD_color_t& col);
	void computeLight();
	// get the computed light color
	const TCOD_color_t& getLightColor(int x, int y);
protected:
	struct Light {
		int x, y, radius;
		TCOD_color_t color;
	};
	TCODList<Light> lights;
	TCOD_color_t* lightmap;
	TCODMap* map;
};