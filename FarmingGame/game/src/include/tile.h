#ifndef TILE_H
#define TILE_H

#define TILE_SPRITE_SIZE 32
#define TILE_SIZE 64
#define TILES_WIDE 24

#include "raylib.h"
#include <vector>

class Object;

class Player;

class TileID {
public:
    TileID();
    TileID(int id, float rotation);
    int GetID();
    float GetRotation();
private:
    int id;
    float rotation;
};

class Tile {
public:
    Tile();
    Tile(int x, int y, int textureID);
    Tile(const Tile& other, int textureID);
    Tile(int x, int y, int textureID, Rectangle sourceRec);
    void draw(Texture2D tileSet, Player* player);
    void draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight, std::vector<int> mudCode);
    void setTextureID(int textureID);
    void setTextureID(int textureID, float rotation);
    void setTextureID(TileID tileID);
    int getTextureID();
    float getIDRotation();
    Tile* interact(int item);
    int getType();
    void codeToID(unsigned int Code);
    int getX();
    int getY();
    Rectangle getSrcRec(int tileId);
private:
    int x;
    int y;
    Rectangle sourceRec;
    bool wet;
    Vector2 originVec;
    TileID textureID;
};

#endif