#include "include/tilemap.h"
#include "include/tile.h"
#include <cstdio>
#include <iostream>
using namespace std;

TileMap::TileMap() 
{
    tileMap.resize(MAP_HEIGHT);
    for (int r = 0; r < MAP_HEIGHT; r++) {
        tileMap[r].resize(MAP_WIDTH);
        for (int c = 0; c < MAP_WIDTH; c++) {
            bool block = false;
            if (c < 15 || r < 9 || c > MAP_WIDTH - 15 || r > MAP_HEIGHT - 9) {
                block = true;
                tileMap[r][c] = new WaterTile(c, r);
            }
            else {
                tileMap[r][c] = new GrassTile(c, r);
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

TileMap::~TileMap() 
{
}

void TileMap::Draw(int playerX, int playerY, Texture2D tileset, int selSlot) 
{
    int mouseX = GetMouseX() + 32;
    int mouseY = GetMouseY() + 32;

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int mouseCol = ((((mouseX + (playerX - screenWidth / 2))) / TILE_SIZE));
    int mouseRow = ((mouseY + (playerY - screenHeight / 2)) / TILE_SIZE);

    int playerCol = (playerX + 32) / TILE_SIZE;
    int playerRow = (playerY + 50) / TILE_SIZE;

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
            thisCode = GetTileCode(row, col);
            tileMap[row][col]->CodeToID(thisCode);
            tileMap[row][col]->Draw(tileset, playerX, playerY, screenWidth, screenHeight);


            if ((col >= playerCol - 1 && col <= playerCol + 1) && (row >= playerRow - 1 && row <= playerRow + 1)) 
            {     
                if (mouseCol == col && mouseRow == row) 
                {
                    Rectangle destinationRec = { ((col * TILE_SIZE) - (playerX - screenWidth / 2)) - 30 , ((row * TILE_SIZE) - (playerY - screenHeight / 2)) - 30, TILE_SIZE-5.6f, TILE_SIZE-5.6f };
                    Vector2 originVec = { 32 , 32 };
                    //DrawRectanglePro(destinationRec, originVec, 0, RED);

                    DrawRectangleRoundedLines(destinationRec, .2f, 5, 4.0f, GOLD);
                    
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        updatedTile = tileMap[row][col]->Interact(selSlot);
                        tileMap[row][col] = updatedTile;

                        if (tileMap[row][col]->GetType() == 1)                        
                        {
                            SetTile(col, row, 1); 
                            thisCode = GetTileCode(row, col);
                            tileMap[row][col]->CodeToID(thisCode);
                            std::cout << "Tile code at (" << col << ", " << row << "): " << thisCode << std::endl;
                        }
                        else
                        {
                            SetTile(col, row, 0);
                            thisCode = GetTileCode(row, col);
                            std::cout << "Tile code  at water (" << col << ", " << row << "): " << edgeMap[(row * 2) + 1][(col * 2) + 1] << std::endl;
                        }
                    }
                }
               
            }
            
            
        }
    }
}


bool TileMap::CheckBlocked(int row, int col)
{
    return tileMap[row][col]->BlockState();
}

float TileMap::GetTileSpeed(int row, int col)
{
    return tileMap[row][col]->TileSpeed();
}

unsigned int TileMap::GetTileCode(int y, int x) {
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

void TileMap::SetTile(int x, int y, int val)
{
    //std::cout << "Tile code at (" << (y + 1) * 2 << ", " << (x + 1) * 2 << "): " << std::endl;
    int newY = (y * 2) + 1;
    int newX = (x * 2) + 1;
    edgeMap[newY][newX] = val;
    UpdateEdge();
    UpdateCorner();
}

void TileMap::UpdateEdge()
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
                edgeMap[r][c] = 0;
                switch (evenRow)
                {
                case false:
                    if ((edgeMap[r][c - 1] == 1) && (edgeMap[r][c + 1] == 1))
                    {
                        edgeMap[r][c] = 1;
                    }
                    break;
                case true:
                    if ((edgeMap[r - 1][c] == 1) && (edgeMap[r + 1][c] == 1))
                    {
                        edgeMap[r][c] = 1;
                    }
                    break;
                }
            }
        }
    }
}

void TileMap::UpdateCorner()
{
    for (int r = 0; r < EDGE_MAP_HEIGHT; r += 2) {
        for (int c = 0; c < EDGE_MAP_WIDTH; c += 2) {
            edgeMap[r][c] = 0;
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
