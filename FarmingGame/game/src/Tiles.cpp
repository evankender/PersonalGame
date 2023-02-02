#include "include/object.h"
#include "include/tile.h"
#include "include/tiles.h"
#include "include/player.h"

Tiles::Tiles()
{
    
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

Tiles::~Tiles()
{
    delete(alwaysFrontTile);
    delete(frontTile);
    delete(pathTile);
    delete(buildingTile);

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
    case 0: 
        alwaysFrontTile = tile;
        break;
    case 1:
        frontTile = tile;
        break; 
    case 2:
        pathTile = tile;
        break;
    case 3:
        buildingTile = tile;
        break;
    case 4:
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
    case 0:
        return alwaysFrontTile;

    case 1:
        return frontTile;

    case 2:
        return pathTile;

    case 3:
        return buildingTile;

    case 4:
        return backTile;
    default:
        break;
    }
}


void Tiles::setObj(Object* obj, int ObjLayer)
{

    switch (ObjLayer)
    {
    case 0:
        alwaysFrontObj = obj;
        break;
    case 1:
        frontObj = obj;
        break;
    case 2:
        pathObj = obj;
        break;
    case 3:
        buildingObj = obj;
        break;
    case 4:
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
    case 0:
        return alwaysFrontObj;
    case 1:
        return frontObj;
    case 2:
        return pathObj;
    case 3:
        return buildingObj;
    case 4:
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