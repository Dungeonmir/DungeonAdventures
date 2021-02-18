#pragma once
#include "libtcod.hpp"
#include "Renderer.h"
struct Tile {
    bool canWalk; // Можно ли пройти через плитку??
    Tile() : canWalk(false) {}
};
static const int ROOM_MAX_SIZE = 10;
static const int ROOM_MIN_SIZE = 9;
class Map 
{
public:
    int width, height;
    Map(int width, int height);
    ~Map();
    bool isWall(int x, int y) const;
    void render(RenderWindow* console) const;
    void setWall(int x, int y);
    int getHeroX();
    int getHeroY();
protected:
    Tile* tiles;
    friend class BspListener;
    int HeroX;
    int HeroY;
    void dig(int x1, int y1, int x2, int y2);
    void createRoom(bool first, int x1, int y1, int x2, int y2);
};