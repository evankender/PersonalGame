#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

class Item;

struct Texture;

class Inventory
{
public:
	Inventory();
	Inventory(int invSize);
	bool addItem(Item* newItem);
	bool addItem(Item* newItem, int invSlot);
    Item* getItem(int invSlot);
	void draw(int x, int y, Texture* imageSet);
private:
	int invSize;
	int slotsFilled;
	bool isFull;
	std::vector<Item*> invItems;
};

#endif