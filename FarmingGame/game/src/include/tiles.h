#ifndef TILES_H
#define TILES_H

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
    int checkExit(Rectangle playerRec);
    void setTileTextureId(int layer, int textureId);
    void interact(TileMap* map, Item* item);
    int getTileId(int layer);
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