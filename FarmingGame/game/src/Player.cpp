#include "include/tilemap.h"
#include "include/tile.h"
#include "include/player.h"

Player::Player(TileMap &tileMap) {
    playerX = (TILE_SIZE * (MAP_WIDTH / 2));
    playerY = (TILE_SIZE * (MAP_HEIGHT / 2));
    sourceRec = { 0, 0, 64, 64 };
    originVec = { 64 , 64 };
    mapPtr = &tileMap;
    playerSpeed = 5.0f;
}

void Player::Move(int dx, int dy) {

    const int newX = playerX + (int)(dx * playerSpeed);
    const int newY = playerY + (int)(dy * playerSpeed);
  
    if (!mapPtr->CheckBlocked(GetRow(newY), GetCol(newX)))
    {
        playerX = newX;
        playerY = newY;
    }
    else
    {
        playerX = playerX - (int)(dx * (playerSpeed));
        playerY = playerY - (int)(dy * (playerSpeed));

    }
}

void Player::DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite)
{

    DrawTexturePro(playerSprite, sourceRec, { (float)screenWidth / 2.0f, (float)screenHeight / 2.0f, 128.0f, 128.0f }, originVec, 0.0f, WHITE);
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
    return ((playerX + 32) / TILE_SIZE);
}

int Player::GetRow()
{
    return ((playerY + 50) / TILE_SIZE);
}

int Player::GetCol(int newX)
{
    return ((newX + 32) / TILE_SIZE);
}

int Player::GetRow(int newY)
{
    return ((newY + 50) / TILE_SIZE);
}