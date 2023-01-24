#include "include/map.h"
#include "include/tile.h"
#include <cstdio>



Map::Map() 
{
    map.resize(MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; i++) {
        map[i].resize(MAP_HEIGHT);
        for (int j = 0; j < MAP_HEIGHT; j++) {
            bool block = false;
            if (i < 15 || j < 9 || i > MAP_WIDTH - 15 || j > MAP_HEIGHT - 9) {
                block = true;
                map[i][j] = new WaterTile(i, j);
            }
            else {
                map[i][j] = new GrassTile(i, j);
            }
        }
    }
}

Map::~Map() 
{
}

void Map::Draw(int playerX, int playerY, Texture2D tileset, int selSlot) 
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int mouseTileX = ((((mouseX + (playerX - screenWidth / 2))) / TILE_SIZE));
    int mouseTileY = ((mouseY + (playerY - screenHeight / 2)) / TILE_SIZE);

    int playerTileX = playerX / TILE_SIZE;
    int playerTileY = playerY / TILE_SIZE;

    int tileWidth = screenWidth / TILE_SIZE;
    int tileHeight = screenHeight / TILE_SIZE;

    int tileStartX = (playerTileX - (tileWidth/2)) - 1;
    int tileStartY = (playerTileY - (tileHeight/2)) - 1;

    int tileEndX = (playerTileX + (tileWidth / 2)) + 2;
    int tileEndY = (playerTileY + (tileHeight/2)) + 2;


    if ((tileStartX) < 0)
    {
        tileStartX = 0;
    }

    if ((tileEndX) > MAP_WIDTH)
    {
        tileEndX = MAP_WIDTH;
    }

    if ((tileStartY) < 0)
    {
        tileStartY = 0;
    }

    if ((tileEndY) > MAP_HEIGHT)
    {
        tileEndY = MAP_HEIGHT;
    }
    Tile* updatedTile;

    
    for (int x = tileStartX; x < tileEndX; x++)
    {
        for (int y = tileStartY; y < tileEndY; y++)
        {
            map[x][y]->Draw(tileset, playerX, playerY, screenWidth, screenHeight);
            if ((x >= playerTileX - 1 && x <= playerTileX + 1) && (y >= playerTileY - 1 && y <= playerTileY + 1)) {
                if (mouseTileX == x && mouseTileY == y) {
                    DrawRectangle(((x * TILE_SIZE) - (playerX - screenWidth / 2)), (y * TILE_SIZE) - (playerY - screenHeight / 2), TILE_SIZE, TILE_SIZE, GREEN);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        updatedTile = map[mouseTileX][mouseTileY]->Interact(selSlot);
                        map[mouseTileX][mouseTileY] = updatedTile;
                    }
                }
            }
            
        }
    }
}


bool Map::CheckBlocked(int tileX, int tileY)
{
    return map[tileX][tileY]->BlockState();
}

float Map::GetTileSpeed(int tileX, int tileY)
{
    return map[tileX][tileY]->TileSpeed();
}




