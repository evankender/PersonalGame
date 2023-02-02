#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "tilemap.h"

class Player {
public:
    Player();
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
    Rectangle getRec();
    Rectangle getRec(int newX, int newY);
    void setDir(int dir);
    void animateMove(int frameCount);
    void setPlayerFrame(int playerFrame);
private:
    int playerX;
    int playerY;
    int playerFrameCount;
    Rectangle sourceRec;
    Vector2 originVec;
    TileMap* mapPtr;
    float playerSpeed;
    Rectangle playerRec;
};

#endif