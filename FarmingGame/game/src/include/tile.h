#include "raylib.h"
#include <vector>


#ifndef TILE_H
#define TILE_H


const int TILE_SPRITE_SIZE = 32;
const int TILE_SPRITE_MAP_WIDTH = TILE_SPRITE_SIZE * 15;
const int TILE_SIZE = 64;
const int DRY_DIRT = 0; 
const int GRASS = 31;
const int WATER = 30;
const int WATER_TICKS = 60;

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
    Tile(int x, int y, int textureID, bool block);
    Tile(const Tile& other, int textureID, bool block);
    virtual void Draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight, std::vector<int> mudCode);
    void SetTextureID(int textureID);
    void SetTextureID(int textureID, float rotation);
    void Tile::SetTextureID(TileID tileID);
    int GetTextureID();
    float GetIDRotation();
    void SetObjectID(int objectID);
    bool BlockState();
    float TileSpeed();
    virtual Tile* Interact(int item);
    virtual int GetType();
    void SetCode(unsigned int newCode);
    virtual void CodeToID(unsigned int Code);
    bool wet;
private:
    bool block;
    TileID textureID;
    float tileSpeed;
    Rectangle sourceRec;
    Rectangle objectSourceRec;
    int objectID;
    int x;
    int y;
    unsigned int code;
    
};

class DirtTile : public Tile {
public:
    DirtTile(int x, int y);
    DirtTile(const Tile& other);
    virtual Tile* Interact(int item);
    void WetTile();
    virtual int GetType();
    void CodeToID(unsigned int code);
private:
    int waterTicks;
};

class GrassTile : public Tile {
public:
    GrassTile(int x, int y);
    GrassTile(const Tile& other);
    virtual Tile* Interact(int item);
    virtual int GetType();
    void CodeToID(unsigned int code);
private:
};

class WaterTile : public Tile {
public:
    WaterTile(int x, int y);
    WaterTile(const Tile& other);
    virtual Tile* Interact(int item);
    virtual int GetType();
    void CodeToID(unsigned int code);
private:
};

#endif