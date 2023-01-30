#include "include/object.h"
#include "include/tile.h"
#include "include/tiles.h"

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
	collisionObj = new Object();
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
    case 5:
        collisionObj = obj;
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

    case 5:
        return collisionObj;

    default:
        break;
    }
}