#ifndef TILES_H
#define TILES_H

#include "include/object.h"
#include "include/tile.h"

class Tiles
{
public:
    Tiles();
    void setTile(Tile* tile, int tileLayer);
    Tile* getTile(int tileLayer);
    void setObj(Object* obj, int objLayer);
    Object* getObj(int tobjLayer);
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
    Object* collisionObj;
};

#endif