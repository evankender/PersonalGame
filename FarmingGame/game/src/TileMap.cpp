#include "include/tilemap.h"
#include "include/tile.h"
#include "include/tiles.h"
#include "include/player.h"
#include <cstdio>
#include <any>
#include <iostream>
#include <unordered_map>
#include <map>
#include "include/tileson.hpp"

using namespace std;

unordered_map<std::string, int> LayersMap =
{
    {"AlwaysFront", 0},
    {"Front", 1},
    {"Paths", 2},
    {"Buildings", 3},
    {"Back", 4},
    {"Collisions", 5}
};

TileMap::TileMap()
{
    tson::Tileson t;
    std::unique_ptr<tson::Map> mapData = t.parse(fs::path("resources/farmmap.tmj"));

    tileMap.resize(MAP_HEIGHT);
    for (int r = 0; r < MAP_HEIGHT; r++)
    {
        tileMap[r].resize(MAP_WIDTH);
        for (int c = 0; c < MAP_WIDTH; c++)
        {
            tileMap[r][c] = new Tiles();
        }
    }

    edgeMap.resize(EDGE_MAP_HEIGHT);
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        edgeMap[r].resize(EDGE_MAP_WIDTH);
        for (int c = 0; c < EDGE_MAP_WIDTH; c++) {
            edgeMap[r][c] = 1;
        }
    }

    if (mapData->getStatus() == tson::ParseStatus::OK)
    {
        for (auto& layer : mapData->getLayers())
        {
            if (layer.getType() == tson::LayerType::ObjectGroup)
            {
                for (auto& obj : layer.getObjects())
                {
                    tson::Vector2i position = obj.getPosition();
                    Object* newObj = new Object();

                    if (LayersMap[layer.getName()] == 5)
                    {
                        newObj = new Object(true);
                    }

                    int tileY = position.y / (32);
                    int tileX = position.x / (32);
                    tileMap[tileY][tileX]->setObj(newObj, LayersMap[layer.getName()]);
                }

            }

            if (layer.getType() == tson::LayerType::TileLayer)
            {
                std::map<std::tuple<int, int>, tson::TileObject> tileData = layer.getTileObjects();
                for (auto& [id, tileObject] : tileData)
                {
                    tson::Tile* tile = tileObject.getTile();
                    if (tile != nullptr)
                    {
                        int tileID = tile->getId();
                        tson::Rect srcRectJson = tile->getDrawingRect();
                        tson::Vector2i position = tileObject.getPositionInTileUnits();

                        Rectangle srcRect = { srcRectJson.x, srcRectJson.y, srcRectJson.width, srcRectJson.height };
                        Tile* tile = new Tile(position.x, position.y, tileID, srcRect);

                        tileMap[position.y][position.x]->setTile(tile, LayersMap[layer.getName()]);

                    }

                }

            }


        }
    }


}


TileMap::~TileMap() 
{
}


void TileMap::Draw(Player player, Texture2D tileSet, int selSlot) 
{
    std::vector<int> mudCode;

    const int mouseX = GetMouseX() + 32;
    const int mouseY = GetMouseY() + 32;

    const int playerX = player.GetX();
    const int playerY = player.GetY();

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const int mouseCol = ((((mouseX + (playerX - screenWidth / 2))) / TILE_SIZE));
    const int mouseRow = ((mouseY + (playerY - screenHeight / 2)) / TILE_SIZE);

    const int playerCol = player.GetCol();
    const int playerRow = player.GetRow();

    const int tileWidth = screenWidth / TILE_SIZE;
    const int tileHeight = screenHeight / TILE_SIZE;

    int colStart = (playerCol - (tileWidth / 2)) - 1;
    int rowStart = (playerRow - (tileHeight / 2)) - 1;

    int colEnd = (playerCol + (tileWidth / 2)) + 2;
    int rowEnd = (playerRow + (tileHeight / 2)) + 2;

    int row = 0;
    int col = 0;

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
    
    for (row = rowStart; row < rowEnd; row++)
    {
        for (col = colStart; col < colEnd; col++)
        {
            //tileMap[row][col]->pathTile->CodeToID(GetPathCode(row, col));

            //if (tileMap[row][col]->pathObj->IsWet()) GetTileCodeMud(row, col, mudCode);

            Tile* backTile = tileMap[row][col]->getTile(4);
            backTile->Draw(tileSet, playerX, playerY, screenWidth, screenHeight);

            Tile* buidlingTile = tileMap[row][col]->getTile(3);
            buidlingTile->Draw(tileSet, playerX, playerY, screenWidth, screenHeight);

            Tile* pathTile = tileMap[row][col]->getTile(2);
            pathTile->Draw(tileSet, playerX, playerY, screenWidth, screenHeight);

            Tile* frontTile = tileMap[row][col]->getTile(1);
            frontTile->Draw(tileSet, playerX, playerY, screenWidth, screenHeight);

            Tile* alwaysFrontTile = tileMap[row][col]->getTile(0);
            alwaysFrontTile->Draw(tileSet, playerX, playerY, screenWidth, screenHeight);



            if ((col >= playerCol - 1 && col <= playerCol + 1) && (row >= playerRow - 1 && row <= playerRow + 1)) 
            {
                if ((playerCol == col) && (playerRow == row))
                {

                    DrawRectanglePro({ (float)(((col * TILE_SIZE) - (playerX - screenWidth / 2))) , (float)(((row * TILE_SIZE) - (playerY - screenHeight / 2))), TILE_SIZE, TILE_SIZE }, {32, 32}, 0.0f, RED);
                }

                if (mouseCol == col && mouseRow == row) 
                {
                    DrawRectangleRoundedLines({ (float)(((col * TILE_SIZE) - (playerX - screenWidth / 2)) - 30) , (float)(((row * TILE_SIZE) - (playerY - screenHeight / 2)) - 30), TILE_SIZE - 5.6f, TILE_SIZE - 5.6f }, .2f, 5, 4.0f, GOLD);
                    
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                       // tileMap[row][col] = tileMap[row][col]->Interact(selSlot);
                        //SetTile(row, col, tileMap[row][col]->GetType());
                    }
                }
               
            }
        }
    }
}


bool TileMap::CheckBlocked(int row, int col)
{
    std::cout << tileMap[row][col]->getObj(5)->isBlocked() << endl;
    return tileMap[row][col]->getObj(5)->isBlocked();
}

float TileMap::GetTileSpeed(int row, int col)
{
    return 1;//tileMap[row][col]->TileSpeed();
}

unsigned int TileMap::GetPathCode(int y, int x) {

    unsigned int code = 0;
    int top = 0;
    int topRight = 0;
    int right = 0;
    int bottomRight = 0;
    int bottom = 0;
    int bottomLeft = 0;
    int left = 0;
    int topLeft = 0;

    y = (y * 2) + 1;
    x = (x * 2) + 1;

    if (edgeMap[y - 1][x] > 1) top = 1;

    if (edgeMap[y - 1][x + 1] > 1) topRight = 1;

    if (edgeMap[y][x + 1] > 1) right = 1;

    if (edgeMap[y + 1][x + 1] > 1) bottomRight = 1;

    if (edgeMap[y + 1][x] > 1) bottom = 1;

    if (edgeMap[y + 1][x - 1] > 1) bottomLeft = 1;

    if (edgeMap[y][x - 1] > 1) left = 1;

    if (edgeMap[y - 1][x - 1] > 1) topLeft = 1;

    code = top + (2 * topRight) + (4 * right) + (8 * bottomRight) + (16 * bottom) + (32 * bottomLeft) + (64 * left) + (128 * topLeft);

    return code;
}

void TileMap::GetPathCodeMud(int y, int x, std::vector<int>& code) 
{
    code.clear();
    code.resize(8);

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
  
    if ((topLeft == 1) && (top == 2) || (topLeft == 2) && (top == 4) || (topLeft == 2) && (top == 2))

    {
        code[0] = (128 * topLeft) + top;
    }
    
    if ((topRight == 1) && (top == 2) || (topRight == 2) && (top == 4) || (topRight == 2) && (top == 2))
    {
        code[1] = top + (2 * topRight);
    }

    if ((topRight == 1) && (right == 2) || (topRight == 2) && (right == 4) || (topRight == 2) && (right == 2))
    {
        code[2] = (2 * topRight) + (4 * right);
    }
    
    if ((bottomRight == 1) && (right == 2) || (bottomRight == 2) && (right == 4) || (bottomRight == 2) && (right == 2))
    {
        code[3] = (4 * right) + (8 * bottomRight);
    }


    if ((bottomRight == 1) && (bottom == 2) || (bottomRight == 2) && (bottom == 4) || (bottomRight == 2) && (bottom == 2))
    {
        code[4] = (8 * bottomRight) + (16 * bottom);
    }

    if ((bottomLeft == 1) && (bottom == 2) || (bottomLeft == 2) && (bottom == 4) || (bottomLeft == 2) && (bottom == 2))
    {
        code[5] = (16 * bottom) + (32 * bottomLeft);
    }

    if ((bottomLeft == 1) && (left == 2) || (bottomLeft == 2) && (left == 4) || (bottomLeft == 2) && (left == 2))
    {
        code[6] = (32 * bottomLeft) + (64 * left);
    }

    if ((topLeft == 1) && (left == 2) || (topLeft == 2) && (left == 4) || (topLeft == 2) && (left == 2))
    {
        code[7] = (64 * left) + (128 * topLeft);
    }
}

void TileMap::SetPathTile(int y, int x, int val)
{
    edgeMap[(y * 2) + 1][(x * 2) + 1] = val;
    UpdateEdge();
    UpdateCorner();
}

void TileMap::UpdateEdge()
{
    for (int r = 0; r < EDGE_MAP_HEIGHT; r++) {
        int c = 0;
        const bool evenRow = ((r % 2) == 0);

        if (evenRow)
        {
            c = 1;
        }

        for (c; c < EDGE_MAP_WIDTH; c += 2) {
            
            if (((r != 0) && (c != 0)) && (r != EDGE_MAP_HEIGHT - 1) && (c != EDGE_MAP_WIDTH - 1))
            {
                edgeMap[r][c] = 1;
                switch (evenRow)
                {
                case false:
                    if ((edgeMap[r][c - 1] > 1) && (edgeMap[r][c + 1] > 1))
                    {
                        edgeMap[r][c] = 2;
                        if ((edgeMap[r][c - 1] == 4) && (edgeMap[r][c + 1] == 4))
                        {
                            edgeMap[r][c] = 4;
                        }
                    }
                    break;
                case true:
                    if ((edgeMap[r - 1][c] > 1) && (edgeMap[r + 1][c] > 1))
                    {
                        edgeMap[r][c] = 2;
                        if ((edgeMap[r - 1][c] == 4) && (edgeMap[r + 1][c] == 4))
                        {
                            edgeMap[r][c] = 4;
                        }

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
            edgeMap[r][c] = 1;
            if (((r != 0) && (c != 0)) && ((r != EDGE_MAP_HEIGHT - 1) && (c != EDGE_MAP_WIDTH - 1)))
            {
                if ((edgeMap[r - 1][c] > 1) && (edgeMap[r + 1][c] > 1) && (edgeMap[r][c + 1] > 1) && (edgeMap[r][c + 1] > 1))
                {
                    edgeMap[r][c] = 2;
                }
                if ((edgeMap[r - 1][c - 1] > 1) && (edgeMap[r + 1][c - 1] > 1) && (edgeMap[r + 1][c + 1] > 1) && (edgeMap[r - 1][c + 1] > 1))
                {
                    edgeMap[r][c] = 2;   
                }
                if ((edgeMap[r - 1][c] == 4) && (edgeMap[r + 1][c] == 4) && (edgeMap[r][c + 1] == 4) && (edgeMap[r][c + 1] == 4))
                {
                    edgeMap[r][c] = 4;
                }
                if ((edgeMap[r - 1][c - 1] == 4) && (edgeMap[r + 1][c - 1] == 4) && (edgeMap[r + 1][c + 1] == 4) && (edgeMap[r - 1][c + 1] == 4))
                {
                    edgeMap[r][c] = 4;
                }

            }
        }
    }
}
