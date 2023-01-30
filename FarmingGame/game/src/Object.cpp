#include "include/object.h"

Object::Object()
{
	block = false;
}

Object::Object(bool _block)
{
	block = _block;
}

bool Object::isBlocked()
{
	return block;
}