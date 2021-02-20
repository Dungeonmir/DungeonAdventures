#include "Map.h"
class BspListener : public ITCODBspCallback {
private:
    Map& map; // a map to dig
    int roomNum; // room number
    int lastx, lasty; // center of the last room
public:
    BspListener(Map& map) : map(map), roomNum(0) {}
    bool visitNode(TCODBsp* node, void* userData) {
        if (node->isLeaf()) {
            int x, y, w, h;
            // dig a room
            TCODRandom* rng = TCODRandom::getInstance();
            w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
            h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
            x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
            y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
            map.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
            if (roomNum != 0) {
                // dig a corridor from last room
                map.dig(lastx, lasty, x + w / 2, lasty);
                map.dig(x + w / 2, lasty, x + w / 2, y + h / 2);
            }
            lastx = x + w / 2;
            lasty = y + h / 2;
            roomNum++;
        }
        return true;
    }
};
Map::Map(int width, int height)
    :width(width), height(height) 
{
    map = new TCODMap(width, height);
    tiles = new Tile[width * height];
    TCODBsp bsp(0, 0, width, height);
    bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
    BspListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
}

Map::~Map() 
{
    delete[] tiles;
    delete map;
}

bool Map::isWall(int x, int y) const 
{
    return !map->isWalkable(x,y);
}

bool Map::isExplored(int x, int y) const {
    return tiles[x + y * width].explored;
}
bool Map::isInFov(int x, int y) const {
    if (map->isInFov(x, y)) {
        tiles[x + y * width].explored = true;
        return true;
    }
    return false;
}
void Map::computeFov(int HeroX_p, int HeroY_p) {
    map->computeFov(HeroX_p, HeroY_p,FOV_RADIUS);
}
int Map::getHeroX()
{
    return HeroX;
}

int Map::getHeroY()
{
    return HeroY;
}

void Map::dig(int x1, int y1, int x2, int y2) {
    if (x2 < x1) {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y2 < y1) {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    for (int tilex = x1; tilex <= x2; tilex++) {
        for (int tiley = y1; tiley <= y2; tiley++) {
            map->setProperties(tilex, tiley, true, true);
        }
    }
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
    dig(x1, y1, x2, y2);
    if (first) {
        // put the player in the first room
        HeroX = (x1 + x2) / 2;
        HeroY = (y1 + y2) / 2;
    }
    else 
    {

    }
    
}

void Map::render(RenderWindow* console) const 
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++) 
        {
            
            if (isInFov(x, y)) {
                console->print(x, y, " ", nullptr, isWall(x, y) ? wall_col : back_col);
            }
            else if (isExplored(x, y)) {
                console->print(x, y, " ", nullptr, isWall(x, y) ? seen_wall_col : seen_back_col);
            }
        }
    }
}
