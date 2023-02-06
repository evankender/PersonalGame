#ifndef TILES_H
#define TILES_H

#include <vector>

class Player;

class Item;

class Tiles
{
public:
    Tiles();
    Tiles(int x,int y);
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
    void addPickUp(Item* item);
    void checkPickUps(Player* player);
    void drawItems(Texture* imageSet, Player* player);
private:

    int x;
    int y;

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

    std::vector<Item*> pickUps;

};

#endif