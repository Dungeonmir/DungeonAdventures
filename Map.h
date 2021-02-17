#pragma once
#include "libtcod.hpp"
#include "Renderer.h"
struct Tile {
    bool canWalk; // ����� �� ������ ����� ������??
    Tile() : canWalk(true) {}
};

class Map 
{
public:
int width, height;
    Map(int width, int height);
    ~Map();
    bool isWall(int x, int y) const;
    void render(RenderWindow* console) const;
    void setWall(int x, int y);
protected:
    Tile* tiles;

    
};