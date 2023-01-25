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
    this->code = 0;
}

Tile::Tile(const Tile& other, int textureID, bool block)
{
    this->x = other.x;
    this->y = other.y;
    this->textureID = textureID;
    this->objectID = -1;
    this->block = block;
    this->tileSpeed = 5.0f;
    float sx = (textureID % 54) * SPRITE_SIZE;
    float sy = (int)(textureID / 54) * SPRITE_SIZE;
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
    float sx = (textureID % 54) * SPRITE_SIZE;
    float sy = (int)(textureID / 54) * SPRITE_SIZE;
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

int Tile::GetType()
{
    return -1;
}

void Tile::SetCode(unsigned int newCode)
{
    this->code = newCode;
}
DirtTile::DirtTile(int x, int y)
    : Tile(x, y, DRY_DIRT, false)
{
    waterTicks = -1;
}

DirtTile::DirtTile(const Tile& other)
    : Tile(other, DRY_DIRT, false)
{
    waterTicks = -1;
}

Tile* DirtTile::Interact(int item)
{
    switch (item)
    {
    case 0: //hoe
        return new WaterTile(*this);
        break;
    case 1: //axe
        break;
    case 2: //water
        this->WetTile();
        break;
    }
    return this;
}

void DirtTile::WetTile()
{
    if (this->waterTicks < 0)
    {
        int newTextureID = this->GetTextureID() + (54*3);
        this->SetTextureID(newTextureID);
    }
    this->waterTicks = WATER_TICKS;
    this->cornersAndEdges.resize(8);
    this->cornersAndEdges = { 0, 0, 0, 0, 0, 0 ,0 ,0 };
}

int DirtTile::GetType()
{
    return 1;
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

int GrassTile::GetType()
{
    return 2;
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

int WaterTile::GetType()
{
    return 0;
}

