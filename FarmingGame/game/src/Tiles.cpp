#include "include/object.h"
#include "include/tile.h"
#include "include/tiles.h"
#include "include/player.h"
#include "include/item.h"
#include "include/tilemap.h"
#include <cstdio>
#include <iostream>

Tiles::Tiles()
{
    x = 0;
    y = 0;
    alwaysFrontTile = new Tile();
    frontTile = new Tile();
    pathTile = new Tile();
    buildingTile = new Tile();
    backTile = new Tile();

	alwaysFrontObj = new Object();
	frontObj = new Object();
	pathObj = new Object();
	buildingObj = new Object();
	backObj = new Object();

}

Tiles::Tiles(int _x, int _y) : Tiles()
{
    x = _x;
    y = _y;
}

Tiles::~Tiles()
{
    delete(alwaysFrontTile);
    delete(frontTile);
    delete(pathTile);
    delete(buildingTile);
    delete(backTile);

    delete(alwaysFrontObj);
    delete(frontObj);
    delete(pathObj);
    delete(buildingObj);
    delete(backObj);
}

void Tiles::setTile(Tile* tile, int tileLayer)
{
    switch (tileLayer)
    {
    case ALWAYSFRONT_LAYER: 
        delete(alwaysFrontTile);
        alwaysFrontTile = tile;
        break;
    case FRONT_LAYER:
        delete(frontTile);
        frontTile = tile;
        break; 
    case PATH_LAYER:
        delete(pathTile);
        pathTile = tile;
        break;
    case BUILDING_LAYER:
        delete(buildingTile);
        buildingTile = tile;
        break;
    case BACK_LAYER:
        delete(backTile);
        backTile = tile;
        break;
    default:
        break;
    }
}

Tile* Tiles::getTile(int tileLayer)
{
    switch (tileLayer)
    {
    case ALWAYSFRONT_LAYER:
        return alwaysFrontTile;

    case FRONT_LAYER:
        return frontTile;

    case PATH_LAYER:
        return pathTile;

    case BUILDING_LAYER:
        return buildingTile;

    case BACK_LAYER:
        return backTile;
    default:
        break;
    }
}


void Tiles::setObj(Object* obj, int ObjLayer)
{
    //std::cout << obj->getX() << "\n";
    switch (ObjLayer)
    {
    case ALWAYSFRONT_LAYER:
        delete(alwaysFrontObj);
        alwaysFrontObj = obj;
        break;
    case FRONT_LAYER:
        delete(frontObj);
        frontObj = obj;
        break;
    case PATH_LAYER:
        delete(pathObj);
        pathObj = obj;
        break;
    case BUILDING_LAYER:
        delete(buildingObj);
        buildingObj = obj;
        break;
    case BACK_LAYER:
        delete(backObj);
        backObj = obj;
        break;
    default:
        break;
    }
}

Object* Tiles::getObj(int objLayer)
{
    switch (objLayer)
    {
    case ALWAYSFRONT_LAYER:
        return alwaysFrontObj;
    case FRONT_LAYER:
        return frontObj;
    case PATH_LAYER:
        return pathObj;
    case BUILDING_LAYER:
        return buildingObj;
    case BACK_LAYER:
        return backObj;
    default:
        break;
    }
}

bool Tiles::checkCollision(Rectangle playerRec)
{
    bool returnBool = false;
    if (alwaysFrontObj->checkCollision(playerRec))
    {
        returnBool = true;
    }
    else if (frontObj->checkCollision(playerRec))
    {
        returnBool = true;
    }
    else if (pathObj->checkCollision(playerRec))
    {
        returnBool = true;
    }
    else if (buildingObj->checkCollision(playerRec))
    {
        returnBool = true;
    }
    else if (backObj->checkCollision(playerRec))
    {
        returnBool = true;
    }
    return returnBool;
}

int Tiles::checkExit(Rectangle playerRec)
{
    int returnLevel = -1;
    if (alwaysFrontObj->isExit())
    {
        returnLevel = alwaysFrontObj->checkExit(playerRec);
    }
    else if (frontObj->isExit())
    {
        returnLevel = frontObj->checkExit(playerRec);
    }
    else if (pathObj->isExit())
    {
        returnLevel = pathObj->checkExit(playerRec);
    }
    else if (buildingObj->isExit())
    {
        returnLevel = buildingObj->checkExit(playerRec);
    }
    else if (backObj->isExit())
    {
        returnLevel = backObj->checkExit(playerRec);
    }
    return returnLevel;
}

void Tiles::setTileTextureId(int tileLayer, int textureId)
{
    
    switch (tileLayer)
    {
    case ALWAYSFRONT_LAYER:
        alwaysFrontTile->setTextureID(textureId);
        break;
    case FRONT_LAYER:
        frontTile->setTextureID(textureId);
        break;
    case PATH_LAYER:
        pathTile->setTextureID(textureId);
        break;
    case BUILDING_LAYER:
        buildingTile->setTextureID(textureId);
        break;
    case BACK_LAYER:
        backTile->setTextureID(textureId);
        break;
    default:
        break;
    }
}

void Tiles::interact(TileMap* currentMap, Item* currentItem)
{
    if(alwaysFrontObj->interact(currentMap, currentItem)) return;
    if(frontObj->interact(currentMap, currentItem)) return;
    if (buildingObj->interact(currentMap, currentItem)) return;
    if(pathObj->interact(currentMap, currentItem)) return;
    if(backObj->interact(currentMap, currentItem)) return;
    return;
}

int Tiles::getTileId(int tileLayer)
{
    switch (tileLayer)
    {
    case ALWAYSFRONT_LAYER:
        return alwaysFrontTile->getTextureID();

    case FRONT_LAYER:
        return frontTile->getTextureID();

    case PATH_LAYER:
        return pathTile->getTextureID();

    case BUILDING_LAYER:
        return buildingTile->getTextureID();

    case BACK_LAYER:
        return backTile->getTextureID();
    default:
        break;
    }
}

void Tiles::addPickUp(Item* item)
{
    pickUps.push_back(item);
}

void Tiles::checkPickUps(Player* player)
{
    for (size_t i = 0; i != pickUps.size(); i++) 
    {
        if (CheckCollisionRecs(player->getRec(), pickUps[i]->getPickUpRec()))
        {
            player->pickUp(pickUps[i]);
            pickUps[i] = new Item();
        }
    }

}

void Tiles::drawItems(Texture* imageSet, Player* player)
{
    for (Item* item : pickUps)
    {
        item->drawItem(imageSet, player->getDestRec(item->getX(), item->getY()));
    }
}