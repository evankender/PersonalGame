#ifndef TILES_H
#define TILES_H

#include "include/object.h"
#include "include/tile.h"

class Player;

class Tiles
{
public:
    Tiles();
    ~Tiles();
    void setTile(Tile* tile, int tileLayer);
    Tile* getTile(int tileLayer);
    void setObj(Object* obj, int objLayer);
    Object* getObj(int tobjLayer);
    bool checkCollision(Rectangle playerRec);
    signed int checkExit(Rectangle playerRec);
private:
    Tile* alwaysFrontTile;
    Tile* frontTile;
    Tile* pathTile;
    Tile* buildingTile;
    Tile* backTile;

    Object* alwaysFrontObj;
    Object* frontObj;
    Object* pathObj;
    Object* buildingObj;
    Object* backObj;
};

#endif