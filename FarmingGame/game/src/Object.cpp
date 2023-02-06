#include "include/object.h"
#include "include/player.h"
#include "include/tileMap.h"
#include "include/item.h"
#include "include/tile.h"
#include "raylib.h"
#include <cstdio>
#include <any>
#include <iostream>

Object::Object()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	block = false;
	objRec = Rectangle{ (float)x,(float)y,(float)width,(float)height };
	newMap = -1;
	layer = -1;
}

Object::Object(int _x, int _y) : Object()
{
	x = _x;
	y = _y;
}


Object::Object(int _x, int _y, int _width, int _height, bool _block, int _newMap, int _layer) : Object(_x, _y)
{
	width = _width;
	height = _height;
	block = _block;
	objRec = Rectangle{ (float)x,(float)y,(float)width,(float)height };
	newMap = _newMap;
	layer = _layer;
}

bool Object::isBlocked()
{
	return block;
}

bool Object::checkCollision(Rectangle playerRec)
{

	bool returnBool = false;
	if (isBlocked() && CheckCollisionRecs(playerRec, objRec))
	{
		returnBool = true;
	}
	return returnBool;
}

int Object::checkExit(Rectangle playerRec)
{
	int returnVal = -1;
	if (isExit() && CheckCollisionRecs(playerRec, objRec))
	{
		returnVal = newMap;
	}
	return returnVal;
}

bool Object::isExit()
{
	return (newMap > -1);
}

int Object::getX()
{
	return x;
}

int Object::getY()
{
	return y;
}


int Object::getLayer()
{
	return layer;
}

bool Object::interact(TileMap* currentMap, Item* currentItem)
{
	return false;
}

int Object::getType()
{
	return DEFAULT_OBJECT;
}

int Object::getTileX()
{
	if (x == 0)
	{
		return 0;
	}
	return x / 32;
}

int Object::getTileY()
{
	if (y == 0)
	{
		return 0;
	}
	return y / 32;
}

void Object::update(TileMap* currentMap, int currentUpdateTicks)
{

}

GrassTile::GrassTile()
{

}

GrassTile::GrassTile(int _x, int _y) : Object(_x, _y, 64, 64, false, -1, 4)
{

}

bool GrassTile::interact(TileMap* currentMap, Item* currentItem)
{
	switch (currentItem->getType())
	{
	case(DEFAULT_ITEM): //default item
		break;
	case(TOOL): //tool
		switch (currentItem->getId())
		{
		case(0): //hoe tool
			currentMap->setTile(new Tile(getTileX(), getTileY(), 0), PATH_LAYER);
			currentMap->setObj(new HoeDirt(getX(), getY()), PATH_LAYER);
			break;
		default:
			break;
		}

		break;
	case(PLACEABLE): //placeable
		currentItem->interact(currentMap, this);
		break;
	default:
		break;
	}
	return true;
}

int GrassTile::getType()
{
	return GRASSTILE;
}

HoeDirt::HoeDirt()
{

}

HoeDirt::HoeDirt(int _x, int _y) : Object(_x, _y, 64, 64, false, -1, 4)
{

}

bool HoeDirt::interact(TileMap* currentMap, Item* currentItem)
{
	switch (currentItem->getType())
	{
	case(DEFAULT_ITEM): //default item
		break;
	case(TOOL): //tool
		switch (currentItem->getId())
		{
		case(1): //pickaxe tool
			currentMap->blankTile(getTileX(), getTileY(), PATH_LAYER);
			currentMap->blankObj(getX(), getY(), PATH_LAYER);
			break;
		default:
			break;
		}
		break;
	case(PLACEABLE): //placeable
		currentItem->interact(currentMap, this);
		break;
	default:
		break;
	}
	return true;
}

int HoeDirt::getType()
{
	return HOEDIRT;
}

Crop::Crop()
{
	cropTicks = 0;
	growthStage = 0;
	maxGrowthStage = -1;
	isWet = false;
}

Crop::Crop(int _x, int _y) : Object(_x, _y, 64, 64, false, -1, 2)
{
	cropTicks = 0;
	growthStage = 0;
	maxGrowthStage = 3;
	isWet = false;
}

void Crop::update(TileMap* currentMap, int currentUpdateTicks)
{
	cropTicks++;
	if (cropTicks > 60)
	{
		cropTicks = 0;
		if (growthStage < maxGrowthStage)
		{
			grow(currentMap);
		}
		
	}
}

void Crop::grow(TileMap* currentMap)
{
	growthStage++;
	int tileTextureId = currentMap->getTileTextureId(getTileX(), getTileY(), getLayer()) + TILES_WIDE;
	currentMap->setTileTextureId(getTileX(), getTileY(), getLayer(), tileTextureId + TILES_WIDE);
	currentMap->setTileTextureId(getTileX(), (getTileY() - 1), getLayer(), tileTextureId);  
}

bool Crop::interact(TileMap* currentMap, Item* currentItem)
{

	Item* newItem;
	Rectangle newPickUpRec;

	switch (currentItem->getType())
	{
	case(DEFAULT_ITEM): //default item
		if (growthStage == maxGrowthStage)
		{
			currentMap->blankTile(getTileX(), getTileY(), BUILDING_LAYER);
			currentMap->blankObj(getX(), getY(), BUILDING_LAYER);
			
		}
		break;
	case(TOOL): //tool
		switch (currentItem->getId())
		{
		case(1): //pickaxe tool
			currentMap->blankTile(getTileX(), getTileY(), BUILDING_LAYER);

			newItem = new Pickaxe();
			newPickUpRec = { (float)getX(), (float)getY(), 32, 32 };
			newItem->setPickUpRec(newPickUpRec);
			newItem->setDestRec(newPickUpRec);
			newItem->setX(getTileX());
			newItem->setY(getTileY());

			currentMap->addPickUp(getTileX(), getTileY(), newItem);
			currentMap->blankObj(getX(), getY(), BUILDING_LAYER);
			break;
		default:
			break;
		}
		break;
	case(PLACEABLE): //placeable
		break;
	default:
		break;
	}
	return true;
}
