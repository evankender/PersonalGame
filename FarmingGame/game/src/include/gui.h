#ifndef GUI_H
#define GUI_H

class GUI {
public:
	GUI();
private:
	int screenWidth;
	int screenHeight;
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

#endif