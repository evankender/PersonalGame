#include "include/tilemap.h"
#include "include/tile.h"
#include "include/player.h"

Player::Player(TileMap &tileMap) {
    playerX = (TILE_SIZE * (MAP_WIDTH / 2));
    playerY = (TILE_SIZE * (MAP_HEIGHT / 2));
    sourceRec = { 0, 0, 64, 64 };
    destVec = { 64 , 64 };
    mapPtr = &tileMap;
    playerSpeed = 1.0f;
}

void Player::move(int dx, int dy) {

    int newX = playerX + (dx * playerSpeed);
    int newY = playerY + (dy * playerSpeed);
    int playerCol = (newX + 30) / TILE_SIZE;
    int playerRow = (newY + 50) / TILE_SIZE;
  
    if (!mapPtr->CheckBlocked(playerRow, playerCol))
    {
        playerX = newX;
        playerY = newY;
    }
    else
    {
        playerX = playerX - (dx * (playerSpeed / 2));
        playerY = playerY - (dy * (playerSpeed / 2));

    }

}

void Player::DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite)
{
    Rectangle destinationRec = { screenWidth / 2, screenHeight / 2, 128, 128 };
    DrawTexturePro(playerSprite, sourceRec, destinationRec, destVec, 0.0f, WHITE);
}

void Player::UpdateSpeed()
{

    int playerCol = (playerX + 32) / TILE_SIZE;
    int playerRow = (playerY + 50) / TILE_SIZE;

    playerSpeed = mapPtr->GetTileSpeed(playerRow, playerCol);
}
