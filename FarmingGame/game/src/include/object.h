#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"


class Object
{
public:
	Object();
	Object(int _x, int _y, int _width, int _height, bool _block);
	Object(int _x, int _y, int _width, int _height, bool _block, int _newMap);
	bool isBlocked();
	bool checkCollision(Rectangle playerRec);
	int checkExit(Rectangle playerRec);
	bool isExit();
	Rectangle objRec;
private:
	int x;
	int y;
	int width;
	int height;
	bool block;
	signed int newMap;
};
#endif