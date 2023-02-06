#include "include/item.h"
#include "include/tile.h"
#include "include/tilemap.h"
#include "include/object.h"
#include "raylib.h"

Item::Item()
{
	amount = -1;
	itemId = -1;
	x = 0;
	y = 0;
	pickUpRec = { 0,0,0,0 };
	srcRec = { 0,0,0,0 };
	destRec = {0,0,0,0};
}

Item::Item(int _amount, int _itemId) : Item()
{
	amount = _amount;
	itemId = _itemId;
	srcRec = getSrcRec();


}

Item::Item(int _amount, int _itemId, int _x, int _y) : Item(_amount, _itemId)
{
	x = _x;
	y = _y;
	
}

int Item::getType()
{
	return DEFAULT_ITEM; //for default
}

int Item::getId()
{
	return itemId;
}

void Item::interact(TileMap* currentMap, Object* object)
{

}

void Item::editAmount(int adjustment)
{
	amount += adjustment;
}

int Item::getAmount()
{
	return amount;
}

void Item::setPickUpRec(Rectangle _pickUpRec)
{
	pickUpRec = _pickUpRec;
}


Rectangle Item::getPickUpRec()
{
	return pickUpRec;
}


void Item::drawItem(Texture* imageSet, Rectangle destRec)
{
	if (itemId != -1)
	{
		//DrawRectanglePro(destRec, { 0, 0 }, 0.0f, GREEN);
		DrawTexturePro(*imageSet, srcRec, destRec, {0 , 0}, 0.0f, WHITE);
	}
}

Rectangle Item::getSrcRec()
{
	Rectangle returnRec = { (float)((itemId % ITEMS_WIDE) * ITEM_SPRITE_SIZE), (float)((int)(itemId / ITEMS_WIDE) * ITEM_SPRITE_SIZE), ITEM_SPRITE_SIZE, ITEM_SPRITE_SIZE };
	return returnRec;
}

void Item::setDestRec(Rectangle _destRec)
{
	destRec = _destRec;
}

int Item::getX()
{
	return x;
}

int Item::getY()
{
	return y;
}

void Item::setX(int _x)
{
	x = _x;
}

void Item::setY(int _y)
{
	y = _y;
}

Tool::Tool() : Item(-1, -1) 
{

}

Tool::Tool(int itemId) : Item(-1, itemId)
{

}

int Tool::getType()
{
	return TOOL; //for tool
}

Hoe::Hoe() : Tool(0) //hoe item Id 0
{

}

Pickaxe::Pickaxe() : Tool(1) //pickaxe item Id 1
{

}

Placeable::Placeable()
{

}

Placeable::Placeable(int _amount, int _itemId) : Item(_amount, _itemId)
{

}

int Placeable::getType()
{
	return PLACEABLE; //for placeable 
}

Seed::Seed()
{

}

Seed::Seed(int amount, int _itemId) : Placeable(amount, _itemId) //hoe item Id 0
{

}

void Seed::interact(TileMap* currentMap, Object* object)
{
	if (object->getType() == HOEDIRT)
	{
		editAmount(-1);
		currentMap->setTile(new Tile(object->getTileX(), object->getTileY(), 993), BUILDING_LAYER);
		currentMap->setObj(new Crop(object->getX(), object->getY()), BUILDING_LAYER);
	}
}