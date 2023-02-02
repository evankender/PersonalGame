#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "include/object.h"
#include <vector>

const int TILE_SPRITE_SIZE = 32;
const int TILE_SPRITE_MAP_WIDTH = TILE_SPRITE_SIZE * 15;
const int TILE_SIZE = 64;
const int DRY_DIRT = 0; 
const int GRASS = 31;
const int WATER = 30;
const int WATER_TICKS = 60;

class Object;

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
    void Draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight);
    void Draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight, std::vector<int> mudCode);
    void SetTextureID(int textureID);
    void SetTextureID(int textureID, float rotation);
    void SetTextureID(TileID tileID);
    int GetTextureID();
    float GetIDRotation();
    Tile* Interact(int item);
    int GetType();
    void CodeToID(unsigned int Code);
    int getX();
    int getY();
private:
    int x;
    int y;
    Rectangle sourceRec;
    bool wet;
    Vector2 originVec;
    TileID textureID;
};

#endif