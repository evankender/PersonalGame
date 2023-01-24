#include "include/tile.h"
#include "raylib.h"
#include <cstdio>

Tile::Tile() : Tile(1, 1, 10, false) {}

Tile::Tile(int x, int y, int textureID, bool block) 
{
    this->x = x;
    this->y = y;
    this->textureID = textureID;
    this->objectID = -1;
    this->block = block;
    this->tileSpeed = 5.0f;
    float sx = (textureID % 54) * 16;
    float sy = (int)(textureID / 54) * 16;
    this->sourceRec = {sx, sy, SPRITE_SIZE, SPRITE_SIZE };
    this->objectSourceRec = { sx, sy, SPRITE_SIZE, SPRITE_SIZE };
}

Tile::Tile(const Tile& other, int textureID, bool block)
{
    this->x = other.x;
    this->y = other.y;
    this->textureID = textureID;
    this->objectID = -1;
    this->block = block;
    this->tileSpeed = 5.0f;
    float sx = (textureID % 54) * 16;
    float sy = (int)(textureID / 54) * 16;
    this->sourceRec = { sx, sy, SPRITE_SIZE, SPRITE_SIZE };
    this->objectSourceRec = { sx, sy, SPRITE_SIZE, SPRITE_SIZE };
}

void Tile::Draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight) 
{ 
    Rectangle destinationRec = { ((x * TILE_SIZE) - (playerX - screenWidth / 2)), (y * TILE_SIZE) - (playerY - screenHeight / 2), TILE_SIZE, TILE_SIZE };
    Vector2 destVec = { 0 , 0 };
    DrawTexturePro(tileSet, sourceRec, destinationRec, destVec, 0.0f, WHITE);
    if (objectID > 0)
    {
        DrawTexturePro(tileSet, objectSourceRec, destinationRec, destVec, 0.0f, WHITE);
    }
}

void Tile::SetTextureID(int newtextureID)
{
    this->textureID = newtextureID;
    float sx = (textureID % 148) * 16;
    float sy = (int)(textureID / 148) * 16;
    this->sourceRec = { sx, sy, SPRITE_SIZE, SPRITE_SIZE };
}

int Tile::GetTextureID()
{
    return this->textureID;
}

void Tile::SetObjectID(int newobjectID)
{
    this->objectID = newobjectID;
    float sx = (objectID % 148) * 16;
    float sy = (int)(objectID / 148) * 16;
    this->objectSourceRec = { sx, sy, SPRITE_SIZE, SPRITE_SIZE };
}

bool Tile::BlockState()
{
    return this->block;
}

float Tile::TileSpeed()
{
    return this->tileSpeed;
}

Tile* Tile::Interact(int item)
{
    return this;
}

DirtTile::DirtTile(int x, int y)
    : Tile(x, y, DRY_DIRT, false)
{
    waterTicks = 0;
}

DirtTile::DirtTile(const Tile& other)
    : Tile(other, DRY_DIRT, false)
{
    waterTicks = 0;
}


Tile* DirtTile::Interact(int item)
{
    return new WaterTile(*this);
}

void DirtTile::WetTile()
{
    this->waterTicks = WATER_TICKS;
}

GrassTile::GrassTile(int x, int y)
    : Tile(x, y, GRASS, false)
{
}

GrassTile::GrassTile(const Tile& other)
    : Tile(other, GRASS, false)
{
}

Tile* GrassTile::Interact(int item)
{
    return new DirtTile(*this);
}


WaterTile::WaterTile(int x, int y)
    : Tile(x, y, WATER, true)
{
}

WaterTile::WaterTile(const Tile& other)
    : Tile(other, WATER, true)
{
}


Tile* WaterTile::Interact(int item)
{
    return new GrassTile(*this);
}

