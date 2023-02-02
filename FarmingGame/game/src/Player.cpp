#include "include/tilemap.h"
#include "include/tile.h"
#include "include/player.h"

Player::Player() {
    playerFrameCount = 0;
    playerX = (TILE_SIZE * (MAP_WIDTH / 2));
    playerY = (TILE_SIZE * (MAP_HEIGHT / 2));
    sourceRec = { 0, 0, 64, 64 };
    originVec = { 35 , 48 };
    mapPtr = nullptr;
    playerSpeed = 4.0f;
    playerRec = { float(playerX + 20), float(playerY + 40), 20, 20 };
}

Player::Player(TileMap &tileMap) {
    playerFrameCount = 0;
    playerX = (TILE_SIZE * (MAP_WIDTH / 2));
    playerY = (TILE_SIZE * (MAP_HEIGHT / 2));
    sourceRec = { 0, 0, 64, 64 };
    originVec = { 35 , 48 };
    mapPtr = &tileMap;
    playerSpeed = 4.0f;
    playerRec = { float(playerX + 20), float(playerY + 40), 20, 20 };
}

void Player::Move(int dx, int dy) {

    const int newX = playerX + (int)(dx * playerSpeed);
    const int newY = playerY + (int)(dy * playerSpeed);

    Rectangle newRec = getRec(newX, newY);
  
    if (!mapPtr->checkAdjacent(GetRow(newY), GetCol(newX), newRec, 0))
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

void Player::DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite)
{

    DrawTexturePro(playerSprite, sourceRec, { (float)screenWidth / 2.0f, (float)screenHeight / 2.0f, 128.0f, 128.0f }, originVec, 0.0f, WHITE);
    //DrawRectanglePro({ (float)(screenWidth / 2), (float)(screenHeight / 2), 45, 32 }, { -7, -46 }, 0.0f, GREEN);
    //DrawText(TextFormat("x %f t %f\n", playerRec.x, playerRec.y), 10, 10, 20, MAROON);
}

void Player::UpdateSpeed()
{
    playerSpeed = mapPtr->GetTileSpeed(GetRow(), GetCol());
}

int Player::GetX()
{
    return playerX;
}

int Player::GetY()
{
    return playerY;
}

int Player::GetCol()
{
    return ((playerX + (TILE_SIZE/2)) / TILE_SIZE);
}

int Player::GetRow()
{
    return ((playerY + (TILE_SIZE / 2)) / TILE_SIZE) + 1;
}

int Player::GetCol(int newX)
{
    return ((newX + (TILE_SIZE / 2)) / TILE_SIZE);
}

int Player::GetRow(int newY)
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