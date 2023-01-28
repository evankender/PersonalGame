#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class tileMap;

class Player {
public:
    Player(TileMap &tileMap);
    void Move(int dx, int dy);
    void DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite);
    void UpdateSpeed();
    int GetX();
    int GetY();
    int GetCol();
    int GetRow();
    int GetCol(int newX);
    int GetRow(int newY);
private:
    int playerX;
    int playerY;
    Rectangle sourceRec;
    Vector2 originVec;
    TileMap* mapPtr;
    float playerSpeed;
};

#endif