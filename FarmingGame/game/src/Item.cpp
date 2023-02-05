#include "include/item.h"
#include "include/tile.h"
#include "include/tilemap.h"
#include "include/object.h"

Item::Item()
{
	amount = -1;
	itemId = -1;
}

Item::Item(int _amount, int _itemId)
{
	amount = _amount;
	itemId = _itemId;
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

Placeable::Placeable(int _amount) : Item(_amount, -1)
{

}

int Placeable::getType()
{
	return PLACEABLE; //for placeable 
}

Seed::Seed()
{

}

Seed::Seed(int amount) : Placeable(amount) //hoe item Id 0
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