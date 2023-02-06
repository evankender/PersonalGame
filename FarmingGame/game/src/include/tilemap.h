
#ifndef TILEMAP_H
#define TILEMAP_H

#define ALWAYSFRONT_LAYER 0
#define FRONT_LAYER 1
#define BUILDING_LAYER 2
#define PATH_LAYER 3
#define BACK_LAYER 4

#include "raylib.h"
#include <string>
#include <vector>
#include <tuple>

const int MAP_WIDTH = 64;
const int MAP_HEIGHT = 64;
const int EDGE_MAP_WIDTH = (MAP_WIDTH*2)+1;
const int EDGE_MAP_HEIGHT = (MAP_HEIGHT*2)+1;

class Player;

class Tiles;

class Tile;

class Object;

class Item;

class TileMap {
public:
    TileMap();
    TileMap(std::string mapLocation);
    ~TileMap();
    void drawBack(Player* player, Texture2D* tileset);
    void drawFront(Player* player, Texture2D* tileset);
    void drawItems(Player* player, Texture2D* imageSet);
    void update(int currentUpdateTicks);
    float getTileSpeed(int tileX, int tileY);
    bool playerAdjacent(int row, int col, Player* player);
    bool checkAdjacent(int playerRow, int playerCol, Rectangle playerRec, int checkType);
    int checkLevelExit(Player* player);
    void checkPickUps(Player* player);
    unsigned int getPathCode(int x, int y);
    void getPathCodeMud(int x, int y, std::vector<int>& mudCode);
    void setPathTile(int row, int col, int val);
    Tile* getTile(int row, int col, int layer);
    void setTile(Tile* tile, int layer);
    void setObj(Object* object, int layer);
    void setTileTextureId(int x, int y, int layer, int textureId);
    void interact(int x, int y, Item* item);
    void delTile(int x, int y, int layer);
    void delObj(int x, int y, int layer);
    void blankTile(int x, int y, int layer);
    void blankObj(int x, int y, int layer);
    std::tuple<int, int, int, int> getDrawDistance(int playerX, int playerY, int playerCol, int playerRow);
    int getTileTextureId(int x, int y, int layer);
    void addPickUp(int x, int y, Item* item);
private:
    void UpdateEdge();
    void UpdateCorner();
    std::vector<std::vector<Tiles*>> tileMap;
    std::vector<std::vector<int>> edgeMap;
};

#endif