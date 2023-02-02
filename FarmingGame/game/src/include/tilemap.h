
#ifndef TILEMAP_H
#define TILEMAP_H

#include "raylib.h"
#include <string>
#include <vector>
#include "include/tile.h"
#include "include/tiles.h"

const int MAP_WIDTH = 64;
const int MAP_HEIGHT = 64;
const int EDGE_MAP_WIDTH = (MAP_WIDTH*2)+1;
const int EDGE_MAP_HEIGHT = (MAP_HEIGHT*2)+1;

class Player;

class Tiles;

class TileMap {
public:
    TileMap();
    TileMap(std::string mapLocation);
    ~TileMap();
    void draw(Player player, Texture2D tileset, Texture2D playerSprite);
    float GetTileSpeed(int tileX, int tileY);
    bool playerAdjacent(int row, int col, Player player);
    bool checkAdjacent(int playerRow, int playerCol, Rectangle playerRec, int checkType);
    int checkLevelExit(Player player);
    unsigned int GetPathCode(int x, int y);
    void GetPathCodeMud(int x, int y, std::vector<int>& mudCode);
    void SetPathTile(int row, int col, int val);
    Tile* getTile(int row, int col, int layer);
    void setTile(Tile* tile, int layer);
private:
    void UpdateEdge();
    void UpdateCorner();
    std::vector<std::vector<Tiles*>> tileMap;
    std::vector<std::vector<int>> edgeMap;
};

#endif