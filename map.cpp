#include "Map.h"
Map::Map(int width, int height)
    :width(width), height(height) 
{
    tiles = new Tile[width * height];
    setWall(10, 10);
    setWall(12, 13);
}

Map::~Map() 
{
    delete[] tiles;
}

bool Map::isWall(int x, int y) const 
{
    return !tiles[x + y * width].canWalk;
}

void Map::setWall(int x, int y) 
{
    tiles[x + y * width].canWalk = false;
}

void Map::render(RenderWindow* console) const 
{

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++) 
        {
            TCOD_color_t back_col = {100,50,10};
            TCOD_color_t* back_p = &back_col;
            TCOD_color_t wall_col = {0, 120, 40};
            TCOD_color_t* wall_col_p = &wall_col;

            console->print(x, y, " ",nullptr,isWall(x,y) ? wall_col_p : back_p);

        }
    }
}
