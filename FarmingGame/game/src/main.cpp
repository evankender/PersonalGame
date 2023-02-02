
#include <raylib.h>
#include <raymath.h>
#include "include/tile.h"
#include "include/tilemap.h"
#include "include/player.h"
#include "include/gui.h"
#include "include/gamestate.h"
#include <cstdlib>
#include <cstdio>

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

GameState game;

int screenWidth = 1600;
int screenHeight = 900;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float inner;
    float radius;

    // Shader locations
    unsigned int posLoc;
    unsigned int innerLoc;
    unsigned int radiusLoc;
} Spot;

void SetupWindow()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "FarmWorld");
    SetTargetFPS(60);
}
//
//Shader SetUpShader()
//{
//    Vector2 spotPos[MAX_SPOTS];
//    Vector2 spotVel[MAX_SPOTS];
//
//    Spot spots[MAX_SPOTS];
//
//    Shader shdrSpot = LoadShader(0, "data/spotlight.fs");
//
//    for (int i = 0; i < MAX_SPOTS; i++)
//    {
//        char posName[32] = "spots[x].pos\0";
//        char innerName[32] = "spots[x].inner\0";
//        char radiusName[32] = "spots[x].radius\0";
//
//        posName[6] = '0' + i;
//        innerName[6] = '0' + i;
//        radiusName[6] = '0' + i;
//
//        spots[i].posLoc = GetShaderLocation(shdrSpot, posName);
//        spots[i].innerLoc = GetShaderLocation(shdrSpot, innerName);
//        spots[i].radiusLoc = GetShaderLocation(shdrSpot, radiusName);
//    }
//
//    // Tell the shader how wide the screen is so we can have
//    // a pitch black half and a dimly lit half.
//    unsigned int wLoc = GetShaderLocation(shdrSpot, "screenWidth");
//    float sw = (float)GetScreenWidth();
//    //SetShaderValue(shdrSpot, wLoc, &sw, SHADER_UNIFORM_FLOAT);
//
//    for (int i = 0; i < MAX_SPOTS; i++)
//    {
//        spots[i].pos.x = (GetScreenWidth() / 2.0f)+28;
//        spots[i].pos.y = GetScreenHeight() / 2.0f;
//        spots[i].vel = Vector2{ 0, 0 };
//
//        spots[i].inner = 28; //(i + 1);
//        spots[i].radius = 100.0f; //(i + 1);
//
//        SetShaderValue(shdrSpot, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
//        SetShaderValue(shdrSpot, spots[i].innerLoc, &spots[i].inner, SHADER_UNIFORM_FLOAT);
//        SetShaderValue(shdrSpot, spots[i].radiusLoc, &spots[i].radius, SHADER_UNIFORM_FLOAT);
//    }
//    return shdrSpot;
//}

int main()
{
    // Initialize window
    SetupWindow();
    game.loadTextures();

    //Shader shdrSpot = SetUpShader();

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        game.update();
        game.draw();
        DrawFPS(0, 0);

        //BeginShaderMode(shdrSpot);
        //DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
        //EndShaderMode();
        
        EndDrawing();
    }

    // Unload resources
    game.unloadTextures();
    // Close window and OpenGL context
    CloseWindow();
    return 0;
}



