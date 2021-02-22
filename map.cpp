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

TCODMap* Map::getMap()
{
    return map;
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
        TCODRandom* rng = TCODRandom::getInstance();
        int nbMonsters = rng->getInt(0, MAX_ROOM_MONSTERS);
        while (nbMonsters > 0) {
            int x = rng->getInt(x1, x2);
            int y = rng->getInt(y1, y2);
            if (canWalk(x, y)) {
                addMonster(x, y);
            }
            nbMonsters--;
        }
    }
    
}

void Map::render(RenderWindow* console) const 
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++) 
        {
            TCOD_color_t* t_dark, *t_light;
            // get the cell dark and lit colors
            if (map->isWalkable(x, y)) {
                t_dark = darkGround;
                t_light = lightGround;
            }
            else {
                t_dark = darkWall;
                t_light = lightWall;
            }
            // render left map
            // hack : for a better look, lights are white and we only use them as
            // a lerp coefficient between dark and light colors.
            // a true light model would multiply the light color with the cell color
            TCOD_color_t Light = engine.shader->getLightColor(x, y);
            TCOD_color_t cellCol = TCOD_color_lerp(*t_dark, *t_light, engine.gammaLookup[Light.r] / 255.0f);
            console->print(x,y, std::string(" "),nullptr, &cellCol);
            for (Actor** iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++)
            {
                TCOD_color_t light = engine.shader->getLightColor((*iterator)->x, (*iterator)->y);
                if (light.r>0)
                {
                    (*iterator)->render(console);
                }
            }

        }
    }
}

bool Map::canWalk(int x, int y) const {
    if (isWall(x, y)) {
        // this is a wall
        return false;
    }
    for (Actor** iterator = engine.actors.begin();
        iterator != engine.actors.end(); iterator++) {
        Actor* actor = *iterator;
        if (actor->x == x && actor->y == y) {
            // there is an actor there. cannot walk
            return false;
        }
    }
    return true;
}

void Map::addMonster(int x, int y) {
    TCODRandom* rng = TCODRandom::getInstance();
    if (rng->getInt(0, 100) < 90) {
        // create an orc
        engine.actors.push(new Actor(x, y, 'O', "orc",2, orc_col));
    }
    else {
        // create a troll
        engine.actors.push(new Actor(x, y, 'T', "troll",5, orc_col));
    }
}
void Map::handOutRandomGold() {
    TCODRandom* rng = TCODRandom::getInstance();
    for (Actor** iterator = engine.actors.begin();
        iterator != engine.actors.end(); iterator++) {
        Actor* actor = *iterator;
        actor->setGold(rng->getInt(0, 5));
    }
    
}