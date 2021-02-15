#pragma once

struct Tile {
    bool canWalk; // Можно ли пройти через плитку??
    Tile() : canWalk(true) {}
};

class Map 
{
public:
int width, height;
    Map(int width, int height);
    ~Map();
    bool isWall(int x, int y) const;
    void render() const;
    void setWall(int x, int y);
protected:
    Tile* tiles;

    
};