#include "raylib.h"
#include <vector>

#ifndef TILE_H
#define TILE_H

const int SPRITE_SIZE = 16;
const int TILE_SIZE = 64;
const int DRY_DIRT = 343;
const int GRASS = 458;
const int WATER = 728;
const int WATER_TICKS = 60;

class Tile {
public:
    Tile();
    Tile(int x, int y, int textureID, bool block);
    Tile(const Tile& other, int textureID, bool block);
    virtual void Draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight);
    void SetTextureID(int textureID);
    int GetTextureID();
    void SetObjectID(int objectID);
    bool BlockState();
    float TileSpeed();
    virtual Tile* Interact(int item);
    virtual int GetType();
    void SetCode(unsigned int newCode);
    int objectID;
    int x;
    int y;
    unsigned int code;
private:
    bool block;
    int textureID;
    float tileSpeed;
    Rectangle sourceRec;
    Rectangle objectSourceRec;
};

class DirtTile : public Tile {
public:
    DirtTile(int x, int y);
    DirtTile(const Tile& other);
    Tile* Interact(int item);
    void WetTile();
    int GetType();
private:
    int waterTicks;
    std::vector<int> cornersAndEdges;
};

class GrassTile : public Tile {
public:
    GrassTile(int x, int y);
    GrassTile(const Tile& other);
    Tile* Interact(int item);
    int GetType();
private:
};

class WaterTile : public Tile {
public:
    WaterTile(int x, int y);
    WaterTile(const Tile& other);
    Tile* Interact(int item);
    int GetType();
private:
};

#endif