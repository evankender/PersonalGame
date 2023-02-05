#include "include/tile.h"
#include "include/player.h"
#include "raylib.h"
#include <cstdio>
#include <unordered_map>
#include <iostream>
using namespace std;


TileID::TileID()
{
    id = -1;
    rotation = 0.0f;
}

TileID::TileID(int _id, float _rotation)
{
    id = _id;
    rotation = _rotation;
}

int TileID::GetID()
{
    return id;
}

float TileID::GetRotation()
{
    return rotation;
}

unordered_map<int, TileID> blobTable = {  //inserting element directly in map
 {0 , TileID(0 , 0.0f)},

 {1  ,   TileID(1  ,  0.0f)}  ,  
 {4  ,   TileID(1  ,  90.0f)}  ,  
 {16  ,   TileID(1  ,  180.0f)}  ,  
 {64  ,   TileID(1  ,  270.0f)}  ,  

 {5  ,   TileID(2 , 0.0f)} , 
 {20 ,  TileID(2 , 90.0f)} , 
 {80 ,  TileID(2 , 180.0f)} , 
 {65 ,  TileID(2 , 270.0f)} , 

 {7 ,  TileID(3 , 0.0f)} , 
 {28 ,  TileID(3 , 90.0f)} , 
 {112 ,  TileID(3 , 180.0f)} , 
 {193 ,  TileID(3 , 270.0f)} , 

 {17 ,  TileID(4 , 0.0f)} , 
 {68 ,  TileID(4 , 90.0f)} , 

 {21 ,  TileID(5 , 0.0f)} , 
 {84 ,  TileID(5 , 90.0f)} , 
 {81 ,  TileID(5 , 180.0f)} , 
 {69 ,  TileID(5 , 270.0f)} , 

 {23 ,  TileID(6 , 0.0f)} , 
 {92 ,  TileID(6 , 90.0f)} , 
 {113 ,  TileID(6 , 180.0f)} , 
 {197 ,  TileID(6 , 270.0f)} , 

 {29 ,  TileID(7 , 0.0f)} , 
 {116 ,  TileID(7 , 90.0f)} , 
 {209 ,  TileID(7 , 180.0f)} , 
 {71 ,  TileID(7 , 270.0f)} , 

 {31 ,  TileID(8 , 0.0f)} , 
 {124 ,  TileID(8 , 90.0f)} , 
 {241 ,  TileID(8 , 180.0f)} , 
 {199 ,  TileID(8 , 270.0f)} , 

 {85 ,  TileID(9 , 0.0f)} , 

 {87 ,  TileID(10  ,  0.0f)} , 
 {93 ,  TileID(10  ,  90.0f)} , 
 {117 ,  TileID(10  ,  180.0f)} , 
 {213 ,  TileID(10  ,  270.0f)} , 

 {95 ,  TileID(11  ,  0.0f)} ,
 {125 ,  TileID(11  ,  90.0f)} ,
 {245 ,  TileID(11  ,  180.0f)} ,
 {215 ,  TileID(11  ,  270.0f)} ,

 {119 ,  TileID(12  ,  0.0f)} ,
 {221 ,  TileID(12  ,  90.0f)} ,

 {127 ,  TileID(13  ,  0.0f)} ,
 {253 ,  TileID(13  ,  90.0f)} ,
 {247 ,  TileID(13  ,  180.0f)} ,
 {223 ,  TileID(13  ,  270.0f)} ,

 {255 ,  TileID(14  ,  0.0f)} ,
};

unordered_map<int, TileID> edgeTable = {  //inserting element directly in map
 {0 , TileID(0 , 0.0f)},

 {130, TileID(32 , 0.0f)},
 {10, TileID(32 , 90.0f)},
 {40, TileID(32 , 180.0f)},
 {160, TileID(32 , 270.0f)},

 {4, TileID(33 , 0.0f)},
 {16, TileID(33 , 90.0f)},
 {64, TileID(33 , 180.0f)},
 {256, TileID(33 , 270.0f)},

 {260, TileID(34 , 0.0f)},
 {20, TileID(34 , 90.0f)},
 {80, TileID(34 , 180.0f)},
 {310, TileID(34 , 270.0f)},

 {8, TileID(35 , 0.0f)},
 {32, TileID(35 , 90.0f)},
 {128, TileID(35 , 180.0f)},
 {512, TileID(35 , 270.0f)},

 {258, TileID(36 , 0.0f)},
 {12, TileID(36 , 90.0f)},
 {48, TileID(36 , 180.0f)},
 {192, TileID(36 , 270.0f)},

 {6, TileID(37 , 0.0f)},
 {24, TileID(37 , 90.0f)},
 {96, TileID(37 , 180.0f)},
 {384, TileID(37 , 270.0f)},


};

Tile::Tile() : Tile(1, 1, -1) {}

Tile::Tile(int _x, int _y, int _textureID) 
{
    x = _x;
    y = _y;
    textureID = TileID(_textureID, 0.0f);
    sourceRec = getSrcRec(textureID.GetID());
    originVec = { TILE_SIZE / 2, TILE_SIZE / 2 };
}

Tile::Tile(const Tile& other, int _textureID) : Tile(other.x, other.y, _textureID)
{
}

Tile::Tile(int _x, int _y, int _textureID, Rectangle _sourceRec) : Tile(_x, _y, _textureID)
{
    sourceRec = _sourceRec;
}

void Tile::draw(Texture2D tileSet, Player* player)
{ 
    if (getTextureID() != -1)
    {
        Rectangle destRec = player->getDestRec(x, y);
        DrawTexturePro(tileSet, sourceRec, destRec, originVec, textureID.GetRotation(), WHITE);
    }
   
}

void Tile::draw(Texture2D tileSet, int playerX, int playerY, int screenWidth, int screenHeight, std::vector<int> mudCode)
{
    if (wet)
    {
        Rectangle destinationRec = { (float)((x * TILE_SIZE) - (playerX - screenWidth / 2)), (float)((y * TILE_SIZE) - (playerY - screenHeight / 2)), TILE_SIZE, TILE_SIZE };

        DrawTexturePro(tileSet, { (float)(textureID.GetID() % 15) * TILE_SPRITE_SIZE, (float)((int)(textureID.GetID() / 15) * TILE_SPRITE_SIZE) + TILE_SPRITE_SIZE, TILE_SPRITE_SIZE, TILE_SPRITE_SIZE }, destinationRec, originVec, textureID.GetRotation() , WHITE);

        for (int i = 0; i < 8; i++)
        {
            if ((mudCode[i] != 0) && (edgeTable.count(mudCode[i])))
            {
                DrawTexturePro(tileSet, { (float)((edgeTable[mudCode[i]].GetID() % 15) * TILE_SPRITE_SIZE), (float)((int)(edgeTable[mudCode[i]].GetID() / 15) * TILE_SPRITE_SIZE), TILE_SPRITE_SIZE, TILE_SPRITE_SIZE }, destinationRec, originVec, edgeTable[mudCode[i]].GetRotation(), WHITE);
            }

        }
    }
    //else Draw(tileSet, player);
}


void Tile::setTextureID(int newtextureID)
{
    textureID = TileID(newtextureID, 0);
    setTextureID(textureID);
}

void Tile::setTextureID(int newtextureID, float rotation)
{
    textureID = TileID(newtextureID, rotation);
    setTextureID(textureID);
}

void Tile::setTextureID(TileID tileID)
{
    textureID = tileID;
    sourceRec = getSrcRec(textureID.GetID());
}

int Tile::getTextureID()
{
    return textureID.GetID();
}

float Tile::getIDRotation()
{
    return textureID.GetRotation();
}

Tile* Tile::interact(int item)
{
    return this;
}

int Tile::getType()
{
    return 0;
}

void Tile::codeToID(unsigned int _code)
{
    setTextureID(blobTable[_code]);
}

int Tile::getX()
{
    return x;
}

int Tile::getY()
{
    return y;
}

Rectangle Tile::getSrcRec(int tileId)
{
    Rectangle returnRec = {(float)((tileId % TILES_WIDE) * TILE_SPRITE_SIZE), (float)((int)(tileId / TILES_WIDE) * TILE_SPRITE_SIZE), TILE_SPRITE_SIZE, TILE_SPRITE_SIZE};
    return returnRec;
}