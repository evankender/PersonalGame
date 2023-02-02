#include "include/gamestate.h"
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>

GameState::GameState()
{
	frameCount = 0;
	currentMapLocation = 0;
	currentMapTexture = 0;
	currentPlayerTexture = 1;
	mapLocations = { "loadmap.tmj", "loadmap2.tmj", "loadmap.tmj" };
	textureLocations = { "tilemap.png", "characterSheet.png" };
	currentMap = TileMap(mapLocations[currentMapLocation]);
	player = Player(currentMap);
}

void GameState::update()
{
	if (!isPaused)
	{
		frameCount++;
		handleInputPlayer();
	}

	int newMapLocation = currentMap.checkLevelExit(player);
	if ((newMapLocation > -1) && (newMapLocation != currentMapLocation))
	{
		loadMap(newMapLocation);
	}
}

void GameState::draw()
{
	currentMap.draw(player, loadedTextures[currentMapTexture], loadedTextures[currentPlayerTexture]);
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

void GameState::handleInputPlayer()
{
	bool moved = false;

	if (IsKeyDown(KEY_W))
	{
		player.Move(0, -1);
		player.animateMove(frameCount);
		player.setDir(8);
		moved = true;
	}
	if (IsKeyDown(KEY_S))
	{
		player.Move(0, 1);
		player.animateMove(frameCount);
		player.setDir(10);
		moved = true;
	}

	if (IsKeyDown(KEY_D))
	{
		player.Move(1, 0);
		player.animateMove(frameCount);
		player.setDir(11);
		moved = true;
	}
	if (IsKeyDown(KEY_A))
	{
		player.Move(-1, 0);
		player.animateMove(frameCount);
		player.setDir(9);
		moved = true;
	}

	if (!moved)
	{
		player.setPlayerFrame(0);
	}

}

void GameState::handleInputHotBar()
{

	switch (GetKeyPressed())
	{
	case KEY_ONE:
		currentSlot = 0;
		break;
	case KEY_TWO:
		currentSlot = 1;
		break;
	case KEY_THREE:
		currentSlot = 2;
		break;
	case KEY_FOUR:
		currentSlot = 3;
		break;
	case KEY_FIVE:
		currentSlot = 4;
		break;
	}
}

void GameState::loadMap(int mapLocationsIndex)
{
	currentMapLocation = mapLocationsIndex;
	currentMap = TileMap(mapLocations[mapLocationsIndex]);
}