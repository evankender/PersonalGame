#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
	Object();
	Object(bool block);
	bool isBlocked();
private:
	bool block;
};
#endif