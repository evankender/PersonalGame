#include "include/inventory.h"
#include "include/item.h"
#include "raylib.h"
#include <vector>
#include <memory>
#include <cstdio>
#include <iostream>

Inventory::Inventory()
{
	invSize = 0;
	slotsFilled = 0;
	isFull = true;
	invItems.resize(invSize);
}

Inventory::Inventory(int _invSize) : Inventory()
{
	invSize = _invSize;
	for (int i = 0; i < invSize; i++)
	{
		invItems.push_back(new Item(-1, -1));
	}
}

bool Inventory::addItem(Item* newItem)
{
	if (slotsFilled != invSize)
	{
		for (int i = 0; i < invSize; i++)
		{
			if (invItems[i]->getId() == -1)
			{
				invItems[i] = newItem;
				slotsFilled++;
				return true;
			}

		}
	}
	return false;
}

bool Inventory::addItem(Item* newItem, int itemSlot)
{
	invItems[itemSlot] = newItem;
	return false;
}

Item* Inventory::getItem(int invSlot)
{
	if (invSlot < invSize)
	{
		std::cout << invItems[invSlot]->getId() << "\n";
		return invItems[invSlot];
	}

	return new Item(-1 , -1);
}

void Inventory::draw(int x, int y, Texture* imageSet)
{
	for (int i = 0; i < invSize; i++)
	{
		const float destRecX = x + (i * 64);
		const float destRecY = y;

		invItems[i]->drawItem(imageSet, {destRecX, destRecY, 64, 64});
	}
}