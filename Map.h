#pragma once
#include "libtcod.hpp"
#include "Renderer.h"
#include "Actor.h"
#include "Engine.h"
#include "Hero.h"
struct Tile {
    bool explored; // has the player already seen this tile ?
    Tile() : explored(false) {}
};

static const int ROOM_MAX_SIZE = 10;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;
static const int FOV_RADIUS = 15;
class Map {
public:
    Map(int width, int height);
    ~Map();
    bool isInFov(int x, int y) const;
    bool isExplored(int x, int y) const;
    bool isWall(int x, int y) const;
    bool canWalk(int x, int y) const;
    void computeFov(int HeroX, int HeroY);
    void addMonster(int x, int y);
    void render(RenderWindow* console) const;
    int width, height;
    int getHeroX();
    int getHeroY();
    TCODMap* getMap();
protected:
    
    TCOD_color_t* lightGround = new TCOD_color_t{ 200, 150, 30 };
    TCOD_color_t* darkGround = new TCOD_color_t{ 0, 0, 50 };
    TCOD_color_t* darkWall = new TCOD_color_t{ 0, 0, 50 };
    TCOD_color_t* lightWall = new TCOD_color_t{ 100, 100, 120 };
    TCOD_color_t* seen_back_col = new TCOD_color_t{ 100,150,100 };
    TCOD_color_t* seen_wall_col = new TCOD_color_t{ 50, 100, 50 };
    TCOD_color_t* orc_col = new TCOD_color_t{ 100,150,50 };
    TCODMap* map;
    Tile* tiles;
    friend class BspListener;
    int HeroX;
    int HeroY;
    void dig(int x1, int y1, int x2, int y2);
    void createRoom(bool first, int x1, int y1, int x2, int y2);
};