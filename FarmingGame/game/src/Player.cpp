#include "include/map.h"
#include "include/tile.h"
#include "include/player.h"

Player::Player(Map &map) {
    this->playerX = (TILE_SIZE * (MAP_WIDTH / 2));
    this->playerY = (TILE_SIZE * (MAP_HEIGHT / 2));
    this->sourceRec = { 0, 0, 64, 64 };
    this->destVec = { 64 , 64 };
    this->mapPtr = &map;
    this->playerSpeed = 1.0f;
}

void Player::move(int dx, int dy) {

    int newX = playerX + (dx * this->playerSpeed);
    int newY = playerY + (dy * this->playerSpeed);

    int playerTileX = newX / TILE_SIZE;
    int playerTileY = newY / TILE_SIZE;

    if (!this->mapPtr->CheckBlocked(playerTileX, playerTileY))
    {
        this->playerX = newX;
        this->playerY = newY;
    }
}

void Player::DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite)
{
    Rectangle destinationRec = { screenWidth / 2, screenHeight / 2, 128, 128 };
    DrawTexturePro(playerSprite, sourceRec, destinationRec, destVec, 0.0f, WHITE);
}

void Player::UpdateSpeed()
{
    int playerTileX = playerX / TILE_SIZE;
    int playerTileY = playerY / TILE_SIZE;

    this->playerSpeed = this->mapPtr->GetTileSpeed(playerTileX, playerTileY);
}
