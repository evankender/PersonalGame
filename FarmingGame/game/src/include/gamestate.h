#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <raylib.h>
#include "include/tilemap.h"
#include "include/player.h"
#include "include/item.h"

enum State { Running, Paused, Loading };

class GameState
{
public:
	GameState();
	void update();
	void updateRunning();
	void updatePaused();
	void updateLoading();
	void draw();
	void drawRunning();
	void drawPaused();
	void drawLoading();
	void loadTextures();
	void unloadTextures();
	void handleInputRunning();
	void handleInputPlayer();
	void handleInputPaused();
	void handleInputHotBar();
	void loadMap(int mapLocationsIndex);
	void drawCursor();
	int getMouseCol(int playerX);
	int getMouseRow(int playerY);
private:
	int frameCount;
	int frameCountLoad;
	int updateTicks;
	int currentMapTexture;
	int currentMapLocation;
	int currentPlayerTexture;
	int currentItemsTexture;
	std::vector<std::string> mapLocations;
	std::vector<std::string> textureLocations;
	std::vector<Texture> loadedTextures;
	//Screen currentScreen;
	State currentState;
	TileMap currentMap;
	Player player;
	int isPaused;
	int currentSlot;
};

#endif