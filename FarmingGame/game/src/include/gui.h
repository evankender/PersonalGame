#include "raylib.h"

class GUI {
public:
	GUI();
	int screenWidth;
	int screenHeight;
private:
};

class Hotbar : public GUI {
public:
	Hotbar(int numSlots);
	void Draw();
	void UpdateSelSlot(int newSlot);
	int GetSelSlot();
private:
	int numSlots;
	int selSlot;
	int itemSize;
};