#include "include/tile.h"
#include "raylib.h"
#include <cstdio>

Tile::Tile() : Tile(1, 1, 10, 1000, false) {}

Tile::Tile(int x, int y, int textureID, int tileMapWidth, bool block) {
    this->x = x;
    this->y = y;
    this->textureID = textureID;
    this->tileMapWidth = tileMapWidth;
    this->block = block;
    this->tileSpeed = 5.0f;
    this->objectID = 0;
    float sx = (textureID % 148) * 16;
    float sy = (int)(textureID / 148) * 16;
    this->sourceRec = {sx, sy, SPRITE_SIZE, SPRITE_SIZE };
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

void Tile::Interact(int item)
{
    switch (this->textureID)
    {
    case 908: //dirt
        if (item == 1) //seed
        {
            this->SetObjectID(5049);  //seed
        }
        break;
    case 9: //seed
        if (item == 0) //hoe
        {
            this->SetTextureID(6);
        }
        break;
    case 766: //grass
        if (item == 0) //hoe
        {
            this->SetTextureID(908);
        }
        break;
    }
}

