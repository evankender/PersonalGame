
#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include <vector>
#include "include/tile.h"


const int MAP_WIDTH = 64;
const int MAP_HEIGHT = 64;
const int EDGE_MAP_WIDTH = (MAP_WIDTH*2)+1;
const int EDGE_MAP_HEIGHT = (MAP_HEIGHT*2)+1;

class Map {
public:
    Map();
    ~Map();
    void Draw(int playerX, int playerY, Texture2D tileset, int selSlot);
    bool CheckBlocked(int tileX, int tileY);
    float GetTileSpeed(int tileX, int tileY);
    unsigned int GetTileCode(int x, int y);
    void SetTile(int x, int y, int val);
    void UpdateEdge();
    void UpdateCorner();
private:
    Image tilemap;
    std::vector<std::vector<Tile*>> map;
    std::vector<std::vector<int>> edgeMap;
};

#endif