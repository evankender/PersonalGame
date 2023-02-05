#ifndef ITEM_H
#define ITEM_H

#define DEFAULT_ITEM -1
#define TOOL 0
#define PLACEABLE 1

class Object;

class TileMap;

class Item
{
public:
	Item();
	Item(int amount, int itemId);
	virtual int getType(); //-1 default 0 tool 1 tile
	virtual void interact(TileMap* currentMap, Object* object);
	int getId();
	void editAmount(int adjustment);
	int getAmount();
private:
	int amount;
	int itemId;
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
	Placeable(int amount);
	virtual int getType();
private:
};

class Seed : public Placeable
{
public:
	Seed();
	Seed(int amount);
	virtual void interact(TileMap* currentMap, Object* object);
};



#endif