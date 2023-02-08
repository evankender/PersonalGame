#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

#define DEFAULT_OBJECT -1
#define GRASSTILE 0
#define HOEDIRT 1

class TileMap;

class Item;

class Object
{
public:
	Object();
	Object(int x, int y);
	Object(int x, int y, int width, int height, bool block, int newMap, int layer);
	bool isBlocked();
	bool checkCollision(Rectangle playerRec);
	int checkExit(Rectangle playerRec);
	bool isExit();
	virtual bool interact(TileMap* currentMap, Item* currentItem);
	virtual int getType();
	int getX();
	int getY();
	int getLayer();
	int getTileX();
	int getTileY();
	virtual void update(TileMap* currentMap, int currentUpdateTicks);
	virtual bool isWet();
	virtual void setWet(bool wetState) {};
private:
	int x;
	int y;
	int width;
	int height;
	bool block;
	int newMap;
	int layer;
	Rectangle objRec;
};

class GrassTile : public Object
{
public:
	GrassTile();
	GrassTile(int x, int y);
	virtual bool interact(TileMap* currentMap, Item* currentItem);
	virtual int getType();
};

class HoeDirt : public Object
{
public:
	HoeDirt();
	HoeDirt(int x, int y);
	virtual bool interact(TileMap* currentMap, Item* currentItem);
	virtual int getType();
	virtual bool isWet();
	void setWet(bool wetState);
private:
	bool isDirtWet;
};

class Crop : public Object
{
public:
	Crop();
	Crop(int _x, int _y);
	void virtual update(TileMap* currentMap, int currentUpdateTicks);
	void grow(TileMap* currentMap);
	virtual bool interact(TileMap* currentMap, Item* currentItem);
	virtual bool isWet();
	void setWet(bool wetState);
private:
	int cropTicks;
	int growthStage;
	int maxGrowthStage;
	bool isCropWet;
};

#endif