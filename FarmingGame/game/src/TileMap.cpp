#include "include/tilemap.h"
#include "include/object.h"
#include "include/tile.h"
#include "include/tiles.h"
#include "include/player.h"
#include <cstdio>
#include <any>
#include <iostream>
#include <unordered_map>
#include <map>
#include "include/tileson.hpp"
#include <tuple>

using namespace std;

unordered_map<std::string, int> LayersMap =
{
    {"AlwaysFront", ALWAYSFRONT_LAYER},
    {"Front", FRONT_LAYER},
    {"Paths", PATH_LAYER},
    {"Buildings", BUILDING_LAYER},
    {"Back", BACK_LAYER},
};

TileMap::TileMap()
{
}

TileMap::TileMap(std::string mapLocation)
{
    const char* c = mapLocation.c_str();
    tson::Tileson t;
    std::unique_ptr<tson::Map> mapData = t.parse(fs::path(TextFormat("resources/maps/%s", c)));

    tileMap.resize(MAP_HEIGHT);
    for (int r = 0; r < MAP_HEIGHT; r++)
    {
        tileMap[r].resize(MAP_WIDTH);
        for (int c = 0; c < MAP_WIDTH; c++)
        {
            tileMap[r][c] = new Tiles(c, r);
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
                    tson::Vector2i size = obj.getSize();
                    std::any blocked = false;
                    std::any exit = -1;

                    if (obj.getProperties().hasProperty("block"))
                    {
                        blocked = obj.getProperties().getProperty("block")->getValue();
                    }

                    if (obj.getProperties().hasProperty("exit"))
                    {
                        exit = obj.getProperties().getProperty("exit")->getValue();
                    }

                    Object* newObj = new Object(position.x, position.y, size.x, size.y, std::any_cast<bool>(blocked), std::any_cast<int>(exit), LayersMap[layer.getName()]);

                    if (obj.getProperties().hasProperty("isGrass"))
                    {
                        newObj = new GrassTile(position.x, position.y);
                    }

                    int tileY = position.y / (TILE_SPRITE_SIZE);
                    int tileX = position.x / (TILE_SPRITE_SIZE);

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
                        int tileId = tile->getId();

                        tson::Rect srcRectJson = tile->getDrawingRect();
                        tson::Vector2i position = tileObject.getPositionInTileUnits();

                        Rectangle srcRect = { srcRectJson.x, srcRectJson.y, srcRectJson.width, srcRectJson.height };
                        Tile* tile = new Tile(position.x, position.y, tileId, srcRect);

                        tileMap[position.y][position.x]->setTile(tile, LayersMap[layer.getName()]);

                    }

                }

            }


        }
    }
}


TileMap::~TileMap() 
{
    for (int r = 0; r < MAP_HEIGHT; r++)
    {
        for (int c = 0; c < MAP_WIDTH; c++)
        {
            //delete(tileMap[r][c]);
        }
    }
}

void TileMap::drawBack(Player* player, Texture2D* tileSet) 
{

    std::vector<int> mudCode;

    auto drawDistance = getDrawDistance(player->getX(), player->getY(), player->getCol(), player->getRow());
    int rowStart, colStart, rowEnd, colEnd;
    std::tie(rowStart, rowEnd, colStart, colEnd) = drawDistance;


    for (int row = rowStart; row < rowEnd; row++)
    {
        for (int col = colStart; col < colEnd; col++)
        {

            //if (tileMap[row][col]->pathObj->IsWet()) GetTileCodeMud(row, col, mudCode);

            Tile* backTile = tileMap[row][col]->getTile(BACK_LAYER);
            backTile->draw(tileSet, player);

            Tile* pathTile = tileMap[row][col]->getTile(PATH_LAYER);
            Object* pathObj = tileMap[row][col]->getObj(PATH_LAYER);
            pathTile->codeToID(getPathCode(row, col));
            pathTile->draw(tileSet, player);
            if (pathObj->isWet())
            {
                getPathCodeMud(row, col, mudCode);
                pathTile->draw(tileSet, player, mudCode);

            }
            
            

            Tile* buidlingTile = tileMap[row][col]->getTile(BUILDING_LAYER);
            buidlingTile->draw(tileSet, player);

            Tile* frontTile = tileMap[row][col]->getTile(FRONT_LAYER);
            frontTile->draw(tileSet, player);

            Tile* alwaysFrontTile = tileMap[row][col]->getTile(ALWAYSFRONT_LAYER);
            alwaysFrontTile->draw(tileSet, player);

        }
    }
}

void TileMap::drawFront(Player* player, Texture2D* tileSet)
{
    auto drawDistance = getDrawDistance(player->getX(), player->getY(), player->getCol(), player->getRow());
    int rowStart, colStart, rowEnd, colEnd;
    std::tie(rowStart, rowEnd, colStart, colEnd) = drawDistance;

    int frontEnd = ((GetScreenHeight() / 2) / TILE_SIZE) + 1;

    for (int row = rowStart; row < rowEnd; row++)
    {
        for (int col = colStart; col < colEnd; col++)
        {
            if ((row-rowStart) > frontEnd)
            {
                Tile* frontTile = tileMap[row][col]->getTile(FRONT_LAYER);
                frontTile->draw(tileSet, player);
            }
            Tile* alwaysFrontTile = tileMap[row][col]->getTile(ALWAYSFRONT_LAYER);
            alwaysFrontTile->draw(tileSet, player);
        }
    }
}

void TileMap::drawItems(Player* player, Texture2D* imageSet)
{
    auto drawDistance = getDrawDistance(player->getX(), player->getY(), player->getCol(), player->getRow());
    int rowStart, colStart, rowEnd, colEnd;
    std::tie(rowStart, rowEnd, colStart, colEnd) = drawDistance;

    for (int row = rowStart; row < rowEnd; row++)
    {
        for (int col = colStart; col < colEnd; col++)
        {

            tileMap[row][col]->drawItems(imageSet, player);
 
        }
    }
}

void TileMap::update(int currentUpdateTicks)
{
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            Object* buidlingObj = tileMap[row][col]->getObj(BUILDING_LAYER);
            buidlingObj->update(this, currentUpdateTicks);
        }
    }
}


float TileMap::getTileSpeed(int row, int col)
{
    return 1;//tileMap[row][col]->TileSpeed();
}

bool TileMap::playerAdjacent(int row, int col, Player* player)
{
    int playerCol = player->getCol();
    int playerRow = player->getRow();
    return ((col >= playerCol - 1 && col <= playerCol + 1) && (row >= playerRow - 1 && row <= playerRow + 1));
}

bool TileMap::checkAdjacent(int playerRow, int playerCol, Rectangle playerRec, int checkType) //0 is for block 1 is for exit
{
    int n = tileMap.size();
    int m = tileMap.size();

    bool result = false;

    if (tileMap[playerRow][playerCol]->checkCollision(playerRec))
    {
        result = true;
        return result;
    }

    for (int dRow = (playerRow > 0 ? -1 : 0); dRow <= (playerRow < n ? 1 : 0);
        ++dRow) 
    {
        for (int dCol = (playerCol > 0 ? -1 : 0);
            dCol <= (playerCol < m ? 1 : 0); ++dCol) 
        {
            if (dRow != 0 || dCol != 0) 
            {
                if (tileMap[playerRow + dRow][playerCol + dCol]->checkCollision(playerRec))
                {
                    result = true;
                    return result;
                }
            }
        }
    }

    return result;
}

int TileMap::checkLevelExit(Player* player) //0 is for block 1 is for exit
{
    int n = tileMap.size();
    int m = tileMap.size();

    const int playerRow = player->getRow();
    const int playerCol = player->getCol();
    const Rectangle playerRec = player->getRec();

    int newMap = tileMap[playerRow][playerCol]->checkExit(playerRec);

    if (newMap > -1)
    {
        return newMap;
    }

    for (int dRow = (playerRow > 0 ? -1 : 0); dRow <= (playerRow < n ? 1 : 0);
        ++dRow)
    {
        for (int dCol = (playerCol > 0 ? -1 : 0);
            dCol <= (playerCol < m ? 1 : 0); ++dCol)
        {
            if (dRow != 0 || dCol != 0)
            {
                newMap = tileMap[playerRow + dRow][playerCol + dCol]->checkExit(playerRec);
                if (newMap > -1)
                {
                    return newMap;
                }
            }
        }
    }
    return newMap;
}

void TileMap::checkPickUps(Player* player) //0 is for block 1 is for exit
{
    int n = tileMap.size();
    int m = tileMap.size();

    const int playerRow = player->getRow();
    const int playerCol = player->getCol();

    tileMap[playerRow][playerCol]->checkPickUps(player);

    for (int dRow = (playerRow > 0 ? -1 : 0); dRow <= (playerRow < n ? 1 : 0);
        ++dRow)
    {
        for (int dCol = (playerCol > 0 ? -1 : 0);
            dCol <= (playerCol < m ? 1 : 0); ++dCol)
        {
            if (dRow != 0 || dCol != 0)
            {
                tileMap[playerRow + dRow][playerCol + dCol]->checkPickUps(player);
            }
        }
    }
}

unsigned int TileMap::getPathCode(int y, int x) {

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

void TileMap::getPathCodeMud(int y, int x, std::vector<int>& code) 
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

void TileMap::setPathTile(int row, int col, int val)
{
    edgeMap[(row * 2) + 1][(col * 2) + 1] = val;
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

Tile* TileMap::getTile(int row, int col, int layer)
{
    return tileMap[row][col]->getTile(layer);
}

void TileMap::setTile(Tile* tile, int layer)
{
    tileMap[tile->getY()][tile->getX()]->setTile(tile, layer);
}

void TileMap::setObj(Object* object, int layer)
{
    tileMap[object->getTileY()][object->getTileX()]->setObj(object, layer);
}

void TileMap::setTileTextureId(int x, int y, int layer, int textureId)
{
    tileMap[y][x]->setTile(new Tile(x, y, textureId), layer);
    //tileMap[y][x]->setTileTextureId(layer, textureId);
}

void TileMap::interact(int x, int y, Item* item)
{
    tileMap[y][x]->interact(this, item);
}

void TileMap::delTile(int x, int y, int layer)
{
    delete(tileMap[y][x]->getTile(layer));
}

void TileMap::delObj(int x, int y, int layer)
{
    delete(tileMap[y][x]->getObj(layer));
}

void TileMap::blankTile(int x, int y, int layer)
{
     //std:cout << x << " " << y << "\n";
     tileMap[y][x]->setTile(new Tile(x, y, -1), layer);
}

void TileMap::blankObj(int x, int y, int layer)
{
    
    int tileX = 0;
    int tileY = 0;
    if (y != 0)
    {
        tileY = y / 32;
    }

    if (x != 0)
    {
        tileX = x / 32;
    }

    tileMap[tileY][tileX]->setObj(new Object(x, y), layer);
}


std::tuple<int, int, int, int> TileMap::getDrawDistance(int playerX, int playerY, int playerCol, int playerRow)
{

    const int tilesWide = GetScreenWidth() / TILE_SIZE;
    const int tilesHigh = GetScreenHeight() / TILE_SIZE;

    int colStart = (playerCol - (tilesWide / 2)) - 1;
    int rowStart = (playerRow - (tilesHigh / 2)) - 2;

    int colEnd = (playerCol + (tilesWide / 2)) + 2;
    int rowEnd = (playerRow + (tilesHigh / 2)) + 2;

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

    return std::make_tuple(rowStart, rowEnd, colStart, colEnd);
}

int TileMap::getTileTextureId(int x, int y, int layer)
{
    return tileMap[y][x]->getTileId(layer);
}

void TileMap::addPickUp(int x, int y, Item* item)
{
    //std:cout << x << " " << y << "\n";
    tileMap[y][x]->addPickUp(item);
}