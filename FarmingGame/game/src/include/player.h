#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <vector>

class Item;

class TileMap;

class Player {
public:
    Player();
    Player(TileMap &tileMap);
    void move(int dx, int dy);
    void drawPlayer(Texture2D playerSprite);
    void updateSpeed();
    int getX();
    int getY();
    int getCol();
    int getRow();
    int getCol(int newX);
    int getRow(int newY);
    Rectangle getRec();
    Rectangle getRec(int newX, int newY);
    void setDir(int dir);
    void animateMove(int frameCount);
    void setPlayerFrame(int playerFrame);
    Item* getCurrentItem();
    void setSelSlot(int selSlot);
    Rectangle getDestRec(int x, int y);

private:
    int playerX;
    int playerY;
    int playerFrameCount;
    Rectangle sourceRec;
    Vector2 originVec;
    TileMap* mapPtr;
    float playerSpeed;
    Rectangle playerRec;
    int selSlot;
    std::vector<Item*> hotBar;
};

#endif