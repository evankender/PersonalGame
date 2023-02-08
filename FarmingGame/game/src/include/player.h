#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <vector>


class Item;

class TileMap;

class Inventory;

class Player {
public:
    Player();
    Player(TileMap &tileMap);
    void move(int dx, int dy);
    void drawPlayer(Texture2D* playerSprite);
    void drawHotBar(Texture2D* imageSet);
    void drawInventory(Texture* imageSet);
    void updateInventory();
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
    bool pickUp(Item* item);
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
    Inventory* inventory;
};

#endif