#include "include/inventory.h"
#include "include/item.h"
#include "raylib.h"
#include <vector>
#include <memory>
#include <cstdio>
#include <iostream>

InvSlot::InvSlot()
{
	item = new Item(-1 ,-1 );
	isHovered = false;
	slotRec = Rectangle{ 0,0,0,0 };
}

void InvSlot::setItem(Item* _item)
{
	item = _item;
}

Item* InvSlot::getItem()
{
	return item;
}

void InvSlot::setSlotRec(Rectangle _slotRec)
{
	slotRec = _slotRec;
}

Rectangle InvSlot::getSlotRec()
{
	return slotRec;
}

void InvSlot::setIsHovered(bool hover)
{
	isHovered = hover;
}


bool InvSlot::getIsHovered()
{
	return isHovered;
}



Inventory::Inventory()
{
	numRows = 0;
	numCols = 0;
	invSize = 0;
	slotsFilled = 0;
	isFull = false;
	invItems.resize(invSize);
	mouseSlot = new InvSlot();
}

Inventory::Inventory(int _numCols, int _numRows) : Inventory()
{
	numCols = _numCols;
	numRows = _numRows;
	invSize = numRows * numCols;

	for (int i = 0; i < invSize; i++)
	{
		invItems.push_back(new InvSlot());
	}
}

bool Inventory::addItem(Item* newItem)
{
	if(slotsFilled != invSize)
	{
		for (int i = 0; i < invSize; i++)
		{
			if (invItems[i]->getItem()->getId() == -1)
			{
				invItems[i]->setItem(newItem);
				slotsFilled++;
				return true;
			}

		}
	}
	return false;
}

bool Inventory::addItem(Item* newItem, int itemSlot)
{
	if ((itemSlot < invSize) && (itemSlot > -1))
	{
		if (invItems[itemSlot]->getItem()->getId() == -1)
		{
			slotsFilled++;
		}

		invItems[itemSlot]->setItem(newItem);
		return true;
	}
	
	return false;
}

Item* Inventory::getItem(int invSlot)
{
	if ((invSlot < invSize) && (invSlot > -1))
	{
		//std::cout << invItems[invSlot]->getId() << "\n";
		return invItems[invSlot]->getItem();
	}

	return new Item(-1 , -1);
}

void Inventory::draw(int x, int y, Texture* imageSet)
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			const float destRecX = ((GetScreenWidth() / 2) - (float(numCols/2) * 64)) + (col * 64);
			const float destRecY = y + (row * 64);

			int index = (numCols * row) + col;

			DrawRectanglePro({ destRecX, destRecY, 64, 64 }, { 0,0 }, 0.0f, ColorAlpha(GRAY, .8f));
			invItems[index]->getItem()->drawItem(imageSet, { destRecX, destRecY, 64, 64 });

		}
	}

}

void Inventory::drawRow(int row, int y, Texture* imageSet)
{
	for (int col = 0; col < numCols; col++)
	{
		const float destRecX = ((GetScreenWidth() / 2) - (float(numCols / 2) * 64)) + (col * 64);
		const float destRecY = y;

		int index = (numCols * row) + col;
		
		DrawRectanglePro({ destRecX, destRecY, 64, 64 }, { 0,0 }, 0.0f, ColorAlpha(GRAY, .8f));

		if (invItems[index]->getIsHovered())
		{
			DrawRectanglePro({ destRecX, destRecY, 64, 64 }, { 0,0 }, 0.0f, ColorAlpha(BLACK, .8f));
		}

		invItems[index]->getItem()->drawItem(imageSet, { destRecX, destRecY, 64, 64 });
		invItems[index]->setSlotRec({ destRecX, destRecY, 64, 64 });

	}
}


void Inventory::drawHotBar(int row, int y, int selSlot, Texture* imageSet)
{
	const float destRecX = ((GetScreenWidth() / 2) - (float(numCols / 2) * 64)) + (selSlot * 64);
	const float destRecY = y;
	DrawRectanglePro({ destRecX, destRecY, 64, 64 }, { 0,0 }, 0.0f, ColorAlpha(BLACK, .9f));
	drawRow(0, y, imageSet);
}

void Inventory::drawPlayerInv(Texture* imageSet)
{
	int row = 0;
	int col = 0;
	float destRecX = ((GetScreenWidth() / 2) - (float(numCols / 2) * 64)) + (col * 64);
	float destRecY = (GetScreenHeight() / 4) + (row * 64);


	for (row = 1; row < numRows; row++)
	{
		for (col = 0; col < numCols; col++)
		{
			destRecX = ((GetScreenWidth() / 2) - (float(numCols / 2) * 64)) + (col * 64);
			destRecY = (GetScreenHeight() / 4) + (row * 64);

			int index = (numCols * row) + col;

			DrawRectanglePro({ destRecX, destRecY, 64, 64 }, { 0,0 }, 0.0f, ColorAlpha(GRAY, .8f));

			if (invItems[index]->getIsHovered())
			{
				DrawRectanglePro({ destRecX, destRecY, 64, 64 }, { 0,0 }, 0.0f, ColorAlpha(BLACK, .8f));
			}

			invItems[index]->getItem()->drawItem(imageSet, { destRecX, destRecY, 64, 64 });
			invItems[index]->setSlotRec({ destRecX, destRecY, 64, 64 });
		}
	}

	drawRow(0, destRecY+64, imageSet);
	Vector2 mousePos = GetMousePosition();

	mouseSlot->getItem()->drawItem(imageSet, { mousePos.x, mousePos.y, 64, 64 });


}

void Inventory::updateInv()
{
	Vector2 mousePos = GetMousePosition();
	for(int i = 0; i < invSize; i++)
	{
		if (CheckCollisionPointRec(mousePos, invItems[i]->getSlotRec()))
		{
			invItems[i]->setIsHovered(true);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				Item* tempItem = mouseSlot->getItem();
				mouseSlot->setItem(invItems[i]->getItem());
				invItems[i]->setItem(tempItem);
			}
		}
		else
		{
			invItems[i]->setIsHovered(false);
		}
	}

}