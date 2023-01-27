#include <raylib.h>
#include <raymath.h>
#include "include/tile.h"
#include "include/tilemap.h"
#include "include/player.h"
#include "include/gui.h"
#include <cstdlib>
#include <cstdio>

Image tilemap;
Texture2D tileset;

Image playerImg;
Texture2D playerSprite;

int screenWidth = 1600;
int screenHeight = 900;

TileMap tileMap;
Player player(tileMap);
Hotbar hotbar(5);

void loadTextures()
{
    tilemap = LoadImage("resources/Tiles/blob.png");
    tileset = LoadTextureFromImage(tilemap);

    playerImg = LoadImage("resources/player.png");
    playerSprite = LoadTextureFromImage(playerImg);
}

void setupWindow()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "FarmWorld");
    SetTargetFPS(60);
}

void HandleInput()
{
	if (IsKeyDown(KEY_D)) player.move(1, 0);
	if (IsKeyDown(KEY_A)) player.move(-1, 0);
	if (IsKeyDown(KEY_W)) player.move(0, -1);
	if (IsKeyDown(KEY_S)) player.move(0, 1);

	switch (GetKeyPressed())
	{
	case KEY_ONE:
		hotbar.UpdateSelSlot(0);
		break;
	case KEY_TWO:
		hotbar.UpdateSelSlot(1);
		break;
	case KEY_THREE:
		hotbar.UpdateSelSlot(2);
		break;
	case KEY_FOUR:
		hotbar.UpdateSelSlot(3);
		break;
	case KEY_FIVE:
		hotbar.UpdateSelSlot(4);
		break;
	}
	return;
}


int main()
{
    // Initialize window
    setupWindow();
    
    // Load tilemap image
    loadTextures();
    
    // Main game loop
    while (!WindowShouldClose()) {

        if (IsWindowResized()) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }

        HandleInput();
       
        BeginDrawing();
        tileMap.Draw(player.playerX, player.playerY, tileset, hotbar.GetSelSlot());

        player.UpdateSpeed();
        player.DrawPlayer(screenWidth, screenHeight, playerSprite);
        hotbar.Draw();

        ClearBackground(WHITE);
        EndDrawing();
    }

    // Unload resources
    UnloadTexture(tileset);
    UnloadImage(tilemap);

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}



