
#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include <vector>
#include "include/tile.h"

const int MAP_WIDTH = 248;
const int MAP_HEIGHT = 248;

class Map {
public:
    Map();
    ~Map();
    void Draw(int playerX, int playerY, Texture2D tileset, int selSlot);
    bool CheckBlocked(int tileX, int tileY);
    float GetTileSpeed(int tileX, int tileY);
private:
    Image tilemap;
    std::vector<std::vector<Tile*>> map;
};


#endif