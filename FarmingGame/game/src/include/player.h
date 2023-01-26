#include "raylib.h"
#include "include/tilemap.h"


class Player {
public:
    int playerX;
    int playerY;
    TileMap * mapPtr;
    Player(TileMap &tileMap);
    void move(int dx, int dy);
    void DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite);
    void UpdateSpeed();
private:
    Rectangle sourceRec;
    Vector2 destVec;
    float playerSpeed;
};