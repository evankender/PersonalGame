#ifndef ITEM_H
#define ITEM_H

#define DEFAULT_ITEM -1
#define TOOL 0
#define PLACEABLE 1

#define ITEM_SPRITE_SIZE 32
#define ITEM_SIZE 64
#define ITEMS_WIDE 4

#include "raylib.h"

class Object;

class TileMap;

class Item
{
public:
	Item();
	Item(int amount, int itemId);
	Item(int amount, int itemId, int _x, int _y);
	virtual int getType(); //-1 default 0 tool 1 tile
	virtual void interact(TileMap* currentMap, Object* object);
	int getId();
	void editAmount(int adjustment);
	int getAmount();
	void setPickUpRec(Rectangle pickUpRec);
	Rectangle getPickUpRec();
	void drawItem(Texture* imageSet, Rectangle destRec);
	Rectangle getSrcRec();
	void setDestRec(Rectangle destRec);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
private:
	int amount;
	int itemId;
	int x;
	int y;
	Rectangle pickUpRec;
	Rectangle srcRec;
	Rectangle destRec;
};

class Tool : public Item
{
public:
	Tool();
	Tool(int itemId);
	virtual int getType();
private:
};

class Hoe : public Tool
{
public:
	Hoe();
private:
};

class Pickaxe : public Tool
{
public:
	Pickaxe();
private:
};

class Placeable : public Item
{
public:
	Placeable();
	Placeable(int amount, int itemId);
	virtual int getType();
private:
};

class Seed : public Placeable
{
public:
	Seed();
	Seed(int amount, int itemId);
	virtual void interact(TileMap* currentMap, Object* object);
};



#endif