#include "include/gamestate.h"
#include "include/item.h"
#include "include/player.h"
#include "include/tilemap.h"
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>

const int TILE_SIZE = 64;

GameState::GameState()
{
	frameCount = 0;
	frameCountLoad = 0;
	updateTicks = 0;
	currentMapLocation = 0;
	currentMapTexture = 0;
	currentPlayerTexture = 1;
	
	mapLocations = { "loadmap.tmj", "loadmap2.tmj", "loadmap.tmj" };
	textureLocations = { "tilemap.png", "characterSheet.png" };
	currentMap = TileMap(mapLocations[currentMapLocation]);
	player = Player(currentMap);
	currentState = Running;
}

void GameState::update()
{

	switch (currentState)
	{
	case Running:
		updateRunning();
		break;
	case Paused:
		updatePaused();
		break;
	case Loading:
		updateLoading();
		break;
	default:
		break;
	}
}

void GameState::updateRunning()
{
	frameCount++;
	updateTicks++;

	handleInputRunning();

	currentMap.update(updateTicks);

	int newMapLocation = currentMap.checkLevelExit(&player);

	if ((newMapLocation > -1) && (newMapLocation != currentMapLocation))
	{
		currentMapLocation = newMapLocation;
		frameCountLoad = 0;
		currentState = Loading;
	}
}

void  GameState::updatePaused()
{
	handleInputPaused();
}

void GameState::updateLoading()
{
	frameCountLoad++;
	if (frameCountLoad == 14) 
	{ 
		loadMap(currentMapLocation);
    }
	if (frameCountLoad == 30)
	{
		frameCountLoad = 0;
		currentState = Running;
	}
}

void GameState::draw()
{
	currentMap.drawBack(&player, loadedTextures[currentMapTexture]);
	player.drawPlayer(loadedTextures[currentPlayerTexture]);
	currentMap.drawFront(&player, loadedTextures[currentMapTexture]);
	switch (currentState)
	{
	case Running:
		drawRunning();
		break;
	case Paused:
		drawPaused();
		break;
	case Loading:
		drawLoading();
		break;
	default:
		break;
	}
}


void GameState::drawRunning()
{
	drawCursor();
}

void GameState::drawPaused()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.5f));
}

void GameState::drawLoading()
{
	Color loadBlack;
	if (frameCountLoad < 15)
	{
		loadBlack = ColorAlpha(BLACK, 0.75f + (frameCountLoad / 50.0f));
	}
	if (frameCountLoad > 14)
	{
		loadBlack = ColorAlpha(BLACK, 1.0f - (frameCountLoad / 30.0f));
	}
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), loadBlack);
}
void GameState::loadTextures()
{
	for (std::string textureLocation : textureLocations)
	{
		const char* c = textureLocation.c_str();
		Image image = LoadImage(TextFormat("resources/textures/%s", c));
		loadedTextures.push_back(LoadTextureFromImage(image));
		UnloadImage(image);
	}
}

void GameState::unloadTextures()
{
	for (int i = 0; i != loadedTextures.size(); ++i) 
	{
		UnloadTexture(loadedTextures[i]);
	}
}

void GameState::handleInputRunning()
{
	handleInputPlayer();
	handleInputHotBar();

	const int mouseX = GetMouseX() + (TILE_SIZE / 2);
	const int mouseY = GetMouseY() + (TILE_SIZE / 2);

	const int playerX = player.getX();
	const int playerY = player.getY();

	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	const int mouseCol = ((((mouseX + (playerX - screenWidth / 2))) / TILE_SIZE));
	const int mouseRow = ((mouseY + (playerY - screenHeight / 2)) / TILE_SIZE);

	if (IsKeyPressed(KEY_ESCAPE))
	{
		currentState = Paused;
	}


	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		currentMap.interact(mouseCol, mouseRow, player.getCurrentItem());
	}
}

void GameState::handleInputHotBar()
{
	switch (GetKeyPressed())
	{
	case KEY_ONE:
		player.setSelSlot(0);
		break;
	case KEY_TWO:
		player.setSelSlot(1);
		break;
	case KEY_THREE:
		player.setSelSlot(2);
		break;
	case KEY_FOUR:
		player.setSelSlot(3);
		break;
	case KEY_FIVE:
		player.setSelSlot(4);
		break;
	}
}

void GameState::handleInputPlayer()
{
	bool moved = false;

	if (IsKeyDown(KEY_W))
	{
		player.move(0, -1);
		player.animateMove(frameCount);
		player.setDir(8);
		moved = true;
	}
	if (IsKeyDown(KEY_S))
	{
		player.move(0, 1);
		player.animateMove(frameCount);
		player.setDir(10);
		moved = true;
	}

	if (IsKeyDown(KEY_D))
	{
		player.move(1, 0);
		player.animateMove(frameCount);
		player.setDir(11);
		moved = true;
	}
	if (IsKeyDown(KEY_A))
	{
		player.move(-1, 0);
		player.animateMove(frameCount);
		player.setDir(9);
		moved = true;
	}

	if (!moved)
	{
		player.setPlayerFrame(0);
	}


}

void GameState::handleInputPaused()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		currentState = Running;
	}
}

void GameState::loadMap(int mapLocationsIndex)
{
	currentMapLocation = mapLocationsIndex;
	currentMap = TileMap(mapLocations[mapLocationsIndex]);
}

void GameState::drawCursor()
{
	const int playerX = player.getX();
	const int playerY = player.getY();
	const int mouseCol = getMouseCol(playerX);
	const int mouseRow = getMouseRow(playerY);
	if (currentMap.playerAdjacent(mouseRow, mouseCol, &player))
	{
		DrawRectangleRoundedLines({ (float)(((mouseCol * TILE_SIZE) - (playerX - GetScreenWidth() / 2)) - 30) , (float)(((mouseRow * TILE_SIZE) - (playerY - GetScreenHeight() / 2)) - 30), TILE_SIZE - 5.6f, TILE_SIZE - 5.6f }, .2f, 5, 4.0f, GOLD);
	}
}

int GameState::getMouseCol(int playerX)
{ 

	return (((((GetMouseX()+32) + (playerX - GetScreenWidth() / 2))) / TILE_SIZE));
}

int GameState::getMouseRow(int playerY)
{
	return (((GetMouseY()+32) + (playerY - GetScreenHeight() / 2)) / TILE_SIZE);
}