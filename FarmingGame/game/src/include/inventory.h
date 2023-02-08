#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "raylib.h"

class Item;

class InvSlot
{
public:
	InvSlot();
	void setItem(Item* item);
	Item* getItem();
	void setSlotRec(Rectangle slotRec);
	Rectangle getSlotRec();
	void setIsHovered(bool hover);
	bool getIsHovered();
	
private:
	Item* item;
	bool isHovered;
	Rectangle slotRec;
};

class Inventory
{
public:
	Inventory();
	Inventory(int numCols, int numRows);
	bool addItem(Item* newItem);
	bool addItem(Item* newItem, int invSlot);
    Item* getItem(int invSlot);
	void draw(int x, int y, Texture* imageSet);
	void drawRow(int row, int y, Texture* imageSet);
	void drawHotBar(int row, int y, int SelSlot, Texture* imageSet);
	void drawPlayerInv(Texture* imageSet);
	void updateInv();
private:
	int numCols;
	int numRows;
	int invSize;
	int slotsFilled;
	bool isFull;
	std::vector<InvSlot*> invItems;
	InvSlot* mouseSlot;
};

#endif