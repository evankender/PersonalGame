#include "raylib.h"

#ifndef TILE_H
#define TILE_H

const int SPRITE_SIZE = 16;
const int TILE_SIZE = 64;

class Tile {
public:
    Tile();
    Tile(int x, int y, int textureID, int tileMapWidth, bool block);
    void Draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight);
    void SetTextureID(int textureID);
    void SetObjectID(int objectID);
    bool BlockState();
    float TileSpeed();
    void Interact(int item);
    int objectID;
private:
    bool block;
    int x;
    int y;
    int textureID;
    int tileMapWidth;
    float tileSpeed;
    Rectangle sourceRec;
    Rectangle objectSourceRec;
};





#endif