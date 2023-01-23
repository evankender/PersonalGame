#include "raylib.h"
#include "map.h"


class Player {
public:
    int playerX;
    int playerY;
    Map * mapPtr;
    Player(Map &map);
    void move(int dx, int dy);
    void DrawPlayer(int screenWidth, int screenHeight, Texture2D playerSprite);
    void UpdateSpeed();
private:
    Rectangle sourceRec;
    Vector2 destVec;
    float playerSpeed;
};