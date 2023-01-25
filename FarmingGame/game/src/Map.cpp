#include "include/map.h"
#include "include/tile.h"
#include <cstdio>
#include <iostream>
using namespace std;

Map::Map() 
{
    map.resize(MAP_HEIGHT);
    for (int r = 0; r < MAP_HEIGHT; r++) {
        map[r].resize(MAP_WIDTH);
        for (int c = 0; c < MAP_WIDTH; c++) {
            bool block = false;
            if (c < 15 || r < 9 || c > MAP_WIDTH - 15 || r > MAP_HEIGHT - 9) {
                block = true;
                map[r][c] = new WaterTile(c, r);
            }
            else {
                map[r][c] = new GrassTile(c, r);
            }
        }
    }

    edgeMap.resize(EDGE_MAP_HEIGHT);
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        edgeMap[r].resize(EDGE_MAP_WIDTH);
        for (int c = 0; c < EDGE_MAP_WIDTH; c++) {
            edgeMap[r][c] = 0;
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

    int mouseCol = ((((mouseX + (playerX - screenWidth / 2))) / TILE_SIZE));
    int mouseRow = ((mouseY + (playerY - screenHeight / 2)) / TILE_SIZE);

    int playerCol = playerX / TILE_SIZE;
    int playerRow = playerY / TILE_SIZE;

    int tileWidth = screenWidth / TILE_SIZE;
    int tileHeight = screenHeight / TILE_SIZE;

    int colStart = (playerCol - (tileWidth/2)) - 1;
    int rowStart = (playerRow - (tileHeight/2)) - 1;

    int colEnd = (playerCol + (tileWidth / 2)) + 2;
    int rowEnd = (playerRow + (tileHeight/2)) + 2;


    if ((colStart) < 0)
    {
        colStart = 0;
    }

    if ((colEnd) > MAP_WIDTH)
    {
        colEnd = MAP_WIDTH;
    }

    if ((rowStart) < 0)
    {
        rowStart = 0;
    }

    if ((rowEnd) > MAP_HEIGHT)
    {
        rowEnd = MAP_HEIGHT;
    }
    Tile* updatedTile;

    
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            unsigned int thisCode;
            map[row][col]->Draw(tileset, playerX, playerY, screenWidth, screenHeight);
            if ((col >= playerCol - 1 && col <= playerCol + 1) && (row >= playerRow - 1 && row <= playerRow + 1)) {        
                if (mouseCol == col && mouseRow == row) {
                    DrawRectangle(((col * TILE_SIZE) - (playerX - screenWidth / 2)), (row * TILE_SIZE) - (playerY - screenHeight / 2), TILE_SIZE, TILE_SIZE, GREEN);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        updatedTile = map[mouseRow][mouseCol]->Interact(selSlot);
                        map[mouseRow][mouseCol] = updatedTile;
                        if (map[mouseRow][mouseCol]->GetType() == 1) {
                            this->SetTile(col, row, 1);
                            this->UpdateEdge();
                            this->UpdateCorner();
                            thisCode = this->GetTileCode(row, col);
                            std::cout << "Tile code at (" << col << ", " << row << "): " << thisCode << std::endl;
                        }

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

unsigned int Map::GetTileCode(int y, int x) {
    unsigned int code = 0;
    y = (y * 2) + 1;
    x = (x * 2) + 1;

    int top = edgeMap[y - 1][x];
    int topRight = edgeMap[y - 1][x + 1];
    int right = edgeMap[y][x + 1];
    int bottomRight = edgeMap[y + 1][x + 1];
    int bottom = edgeMap[y + 1][x];
    int bottomLeft = edgeMap[y + 1][x - 1];
    int left = edgeMap[y][x - 1];
    int topLeft = edgeMap[y - 1][x - 1];

    code = top + (2 * topRight) + (4 * right) + (8 * bottomRight) + (16 * bottom) + (32 * bottomLeft) + (64 * left) + (128 * topLeft);

    return code;
}

void Map::SetTile(int x, int y, int val)
{
    //std::cout << "Tile code at (" << (y + 1) * 2 << ", " << (x + 1) * 2 << "): " << std::endl;
    int newY = (y * 2) + 1;
    int newX = (x * 2) + 1;
    edgeMap[newY][newX] = 1;

    /*
    if (edgeMap[newY - 2][newX] == 1)
    {
        edgeMap[newY - 1][newX] = 1;
    }

    if (edgeMap[newY + 2][newX] == 1)
    {
        edgeMap[newY + 1][newX] = 1;
    }

    if (edgeMap[newY][newX - 2] == 1)
    {
        edgeMap[newY][newX - 1] = 1;
    }

    if (edgeMap[newY][newX + 2] == 1)
    {
        edgeMap[newY][newX + 1] = 1;
    }
    */
}

void Map::UpdateEdge()
{
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        int c = 0;
        bool evenRow = ((r % 2) == 0);

        if (evenRow)
        {
            c = 1;
        }

        for (c; c < EDGE_MAP_WIDTH; c += 2) {
            if (((r != 0) && (c != 0)) && (r != EDGE_MAP_HEIGHT - 1) && (c != EDGE_MAP_WIDTH - 1))
            {
                switch (evenRow)
                {
                case false:
                    if ((this->edgeMap[r][c - 1] == 1) && (this->edgeMap[r][c + 1] == 1))
                    {
                        this->edgeMap[r][c] = 1;
                    }
                    break;
                case true:
                    if ((this->edgeMap[r - 1][c] == 1) && (this->edgeMap[r + 1][c] == 1))
                    {
                        this->edgeMap[r][c] = 1;
                    }
                    break;
                }
            }
        }
    }
}

void Map::UpdateCorner()
{
    for (int r = 0; r < EDGE_MAP_HEIGHT; r += 2) {
        for (int c = 0; c < EDGE_MAP_WIDTH; c += 2) {
            if (((r != 0) && (c != 0)) && ((r != EDGE_MAP_HEIGHT - 1) && (c != EDGE_MAP_WIDTH - 1)))
            {
                if ((edgeMap[r - 1][c] == 1) && (edgeMap[r + 1][c] == 1) && (edgeMap[r][c + 1] == 1) && (edgeMap[r][c + 1] == 1))
                {
                    edgeMap[r][c] = 1;
                }
                if ((edgeMap[r - 1][c - 1] == 1) && (edgeMap[r + 1][c - 1] == 1) && (edgeMap[r + 1][c + 1] == 1) && (edgeMap[r - 1][c + 1] == 1))
                {
                    edgeMap[r][c] = 1;
                }
            }
        }
    }
}
