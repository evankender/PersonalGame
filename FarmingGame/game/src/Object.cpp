#include "include/object.h"
#include "include/player.h"
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
}

Object::Object(int _x, int _y, int _width, int _height, bool _block)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	block = _block;
	objRec = Rectangle{ (float)x,(float)y,(float)width,(float)height };
	newMap = -1;
}

Object::Object(int _x, int _y, int _width, int _height, bool _block, int _newMap)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	block = _block;
	objRec = Rectangle{ (float)x,(float)y,(float)width,(float)height };
	newMap = _newMap;
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