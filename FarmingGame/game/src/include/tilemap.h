
#ifndef TILEMAP_H
#define TILEMAP_H

#include "raylib.h"
#include <vector>
#include "include/tile.h"
#include "include/tiles.h"

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;
const int EDGE_MAP_WIDTH = (MAP_WIDTH*2)+1;
const int EDGE_MAP_HEIGHT = (MAP_HEIGHT*2)+1;


class Player;

class Tiles;

class TileMap {
public:
    TileMap();
    ~TileMap();
    void Draw(Player player, Texture2D tileset, int selSlot);
    bool CheckBlocked(int tileX, int tileY);
    float GetTileSpeed(int tileX, int tileY);
    unsigned int GetPathCode(int x, int y);
    void GetPathCodeMud(int x, int y, std::vector<int>& mudCode);
    void SetPathTile(int x, int y, int val);
private:
    void UpdateEdge();
    void UpdateCorner();
    std::vector<std::vector<Tiles*>> tileMap;
    std::vector<std::vector<int>> edgeMap;
};

#endif