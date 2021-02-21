#include "Shader.h"

Shader::~Shader()
{
}

void Shader::init(TCODMap* map) {
	this->map = map;
	int size = map->getWidth() * map->getHeight(); //Получение размера карты
	lightmap = new TCOD_color_t[size]; // Для каждой ячейки карты создаетя переменная цвет
}

int Shader::addLight(int x, int y, int radius, const TCOD_color_t& color)
{
	int id = lights.size();
	Light l;
	l.x = x;
	l.y = y;
	l.radius = radius;
	l.color = color;
	lights.push(l);
	return id;
}
void Shader::updateLight(int id, int x, int y, int radius, const TCOD_color_t& color)
{
	Light* l = lights.begin() + id;
	l->x = x;
	l->y = y;
	l->radius = radius;
	l->color = color;
}

const TCOD_color_t& Shader::getLightColor(int x, int y) 
{ 
	return lightmap[x + y * map->getWidth()]; 
}

void Shader::computeLight() {
    // turn off all lights
    //std::fill_n(lightmap, sizeof(TCODColor) * map->getWidth() * map->getHeight(), 0); //Поменять на это если будет работать
    memset(lightmap, 0, sizeof(TCOD_color_t) * map->getWidth() * map->getHeight()); // Обнуляет массив цветов
    for (Light* l = lights.begin(); l != lights.end(); l++) {
        // compute the potential visible set for this light
        int minx = l->x - l->radius;
        int miny = l->y - l->radius;
        int maxx = l->x + l->radius;
        int maxy = l->y + l->radius;
        minx = MAX(0, minx);
        miny = MAX(0, miny);
        maxx = MIN(maxx, map->getWidth() - 1);
        maxy = MIN(maxy, map->getHeight() - 1);
        float offset = 1.0f / (1.0f + (float)(l->radius * l->radius) / 20);
        float factor = 1.0f / (1.0f - offset);
        // compute the light's fov
        TCODMap lmap(maxx - minx + 1, maxy - miny + 1);
        for (int x = minx; x <= maxx; x++) {
            for (int y = miny; y <= maxy; y++) {
                lmap.setProperties(x - minx, y - miny, map->isWalkable(x, y), map->isTransparent(x, y));
            }
        }
        lmap.computeFov(l->x - minx, l->y - miny, l->radius);
        // compute the light's contribution
        // double invSquaredRadius=1.0 / (l->radius*l->radius);
        for (int x = minx; x <= maxx; x++) 
        {
            for (int y = miny; y <= maxy; y++) 
            {
                if (lmap.isInFov(x - minx, y - miny)) 
                {
                    int squaredDist = (l->x - x) * (l->x - x) + (l->y - y) * (l->y - y);
                    // basic
                    // double coef = 1.0-squaredDist*invSquaredRadius;
                    // invsqr1
                    // double coef=(1.0f/(1.0f+(float)(squaredDist)));
                    // invsqr2
                    double coef = (1.0f / (1.0f + (float)(squaredDist) / 20) - offset) * factor;
                    TCOD_color_t* col = &lightmap[x + y * map->getWidth()];
                    *col = TCOD_color_add(*col, l->color);
                    *col = TCOD_color_multiply_scalar(*col, coef);
                }
            }
        }
    }
}
