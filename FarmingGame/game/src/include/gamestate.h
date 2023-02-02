#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <raylib.h>
#include "include/tilemap.h"
#include "include/player.h"

class Screen;

class GameState
{
public:
	GameState();
	void update();
	void draw();
	void loadTextures();
	void unloadTextures();
	void handleInputPlayer();
	void handleInputHotBar();
	void loadMap(int mapLocationsIndex);
private:
	int frameCount;
	int currentMapTexture;
	int currentMapLocation;
	int currentPlayerTexture;
	std::vector<std::string> mapLocations;
	std::vector<std::string> textureLocations;
	std::vector<Texture> loadedTextures;
	//Screen currentScreen;
	TileMap currentMap;
	Player player;
	bool isPaused;
	int currentSlot;
};

#endif