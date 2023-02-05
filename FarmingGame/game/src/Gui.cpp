#include "include/gui.h"
#include "raylib.h"

//#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

GUI::GUI()
{
   
}

Hotbar::Hotbar(int _numSlots)
{
    numSlots = _numSlots;
    selSlot = 0;
    itemSize = 84;
}

void Hotbar::draw()
{
    const int hotbarX = (GetScreenWidth() / 2) - ((numSlots * itemSize) / 2);
    const int hotbarY = GetScreenHeight() - itemSize - 10;
    for (int i = 0; i < numSlots; i++)
    {
        DrawRectangle(hotbarX + (i * itemSize), hotbarY, itemSize, itemSize, BLUE);
        if (i == selSlot) 
        {
            DrawRectangle(hotbarX + (i * itemSize)-1, hotbarY-1, itemSize+2, itemSize+2, RED);
        }
    }
}

void Hotbar::UpdateSelSlot(int newSlot)
{
    selSlot = newSlot;
}

int Hotbar::GetSelSlot()
{
    return selSlot;
}