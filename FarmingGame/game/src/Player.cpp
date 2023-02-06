#include "include/player.h"
#include "include/tilemap.h"
#include "include/tile.h"
#include "include/item.h"
#include "include/inventory.h"
#include <memory>
#include <cstdio>
#include <iostream>

Player::Player() {
    playerFrameCount = 0;
    playerX = (TILE_SIZE * (MAP_WIDTH / 2));
    playerY = (TILE_SIZE * (MAP_HEIGHT / 2));
    sourceRec = { 0, 0, 64, 64 };
    originVec = { 35 , 48 };
    mapPtr = nullptr;
    playerSpeed = 4.0f;
    playerRec = { float(playerX + 20), float(playerY + 40), 20, 20 };
    selSlot = 0;
    hotBar = new Inventory(5);
    hotBar->addItem(new Hoe());
    hotBar->addItem(new Pickaxe());
    hotBar->addItem(new Seed(5, 5));
}

Player::Player(TileMap &tileMap) : Player() {
    mapPtr = &tileMap;
}

void Player::move(int dx, int dy) {

    const int newX = playerX + (int)(dx * playerSpeed);
    const int newY = playerY + (int)(dy * playerSpeed);

    Rectangle newRec = getRec(newX, newY);
  
    if (!mapPtr->checkAdjacent(getRow(newY), getCol(newX), newRec, 0))
    {
        playerX = newX;
        playerY = newY;
        playerRec = newRec;
    }
    else
    {
        playerX = playerX;
        playerY = playerY;
    }
}

void Player::drawPlayer(Texture2D* playerSprite, Texture2D* imageSet)
{

    DrawTexturePro(*playerSprite, sourceRec, { (float)GetScreenWidth()/ 2.0f, (float)GetScreenHeight() / 2.0f, 128.0f, 128.0f }, originVec, 0.0f, WHITE);
    //DrawRectanglePro({ (float)(screenWidth / 2), (float)(screenHeight / 2), 45, 32 }, { -7, -46 }, 0.0f, GREEN);
    DrawText(TextFormat("x %f t %f\n", playerRec.x, playerRec.y), 10, 10, 20, MAROON);



    int itemSize = 64;
    const int hotbarX = (GetScreenWidth() / 2) - ((5 * itemSize) / 2);
    const int hotbarY = GetScreenHeight() - itemSize - 10;
    for (int i = 0; i < 5; i++)
    {
        DrawRectangle(hotbarX + (i * itemSize), hotbarY, itemSize, itemSize, BLUE);
        if (i == selSlot)
        {
            DrawRectangle(hotbarX + (i * itemSize) - 1, hotbarY - 1, itemSize + 2, itemSize + 2, RED);
        }

    }

    hotBar->draw(hotbarX, hotbarY, imageSet);
}

void Player::updateSpeed()
{
    playerSpeed = mapPtr->getTileSpeed(getRow(), getCol());
}

int Player::getX()
{
    return playerX;
}

int Player::getY()
{
    return playerY;
}

int Player::getCol()
{
    return ((playerX + (TILE_SIZE/2)) / TILE_SIZE);
}

int Player::getRow()
{
    return ((playerY + (TILE_SIZE / 2)) / TILE_SIZE) + 1;
}

int Player::getCol(int newX)
{
    return ((newX + (TILE_SIZE / 2)) / TILE_SIZE);
}

int Player::getRow(int newY)
{
    return ((newY + (TILE_SIZE / 2)) / TILE_SIZE);
}

Rectangle Player::getRec()
{
    return playerRec;
}

Rectangle Player::getRec(int newX, int newY)
{
    Rectangle newPlayerRec = { float(newX/2)+20, float(newY/2)+35, 20, 20 };
    return newPlayerRec;
}

void Player::setDir(int dir)
{
    sourceRec.y = (float)(TILE_SIZE * dir);
}

void Player::animateMove(int frameCount)
{
    if (frameCount % 6 == 1)
    {
        playerFrameCount++;
    }

    if (playerFrameCount > 7)
    {
        playerFrameCount = 0;
    }
    sourceRec.x = (float)(TILE_SIZE * playerFrameCount);
}

void Player::setPlayerFrame(int playerFrame)
{
    playerFrameCount = playerFrame;
    sourceRec.x = (float)(TILE_SIZE * playerFrameCount);
}

Item* Player::getCurrentItem()
{
    return hotBar->getItem(selSlot);
}

void Player::setSelSlot(int _selSlot)
{
    selSlot = _selSlot;
}

Rectangle Player::getDestRec(int x, int y)
{
    Rectangle returnRec = { (float)((x * TILE_SIZE) - (playerX - (GetScreenWidth() / 2))), (float)((y * TILE_SIZE) - (playerY - (GetScreenHeight() / 2))), TILE_SIZE, TILE_SIZE };
    return returnRec;
}

void Player::pickUp(Item* item)
{
    hotBar->addItem(item);
}