/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and run premake 

*/

#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{
    // Initialize the window and rendering context
    InitWindow(screenWidth, screenHeight, "2D Movement Example");

    // Create a player object with a position and velocity
    Vector2 playerPos = { screenWidth / 2, screenHeight / 2 };
    Vector2 playerVel = { 0, 0 };

    // Set the player's speed
    float playerSpeed = 5.0f;

    SetTargetFPS(60); // Set the desired frame rate

    // Main game loop
    while (!WindowShouldClose())
    {
        // Handle input
        if (IsKeyDown(KEY_RIGHT)) playerVel.x = playerSpeed;
        else if (IsKeyDown(KEY_LEFT)) playerVel.x = -playerSpeed;
        else playerVel.x = 0;

        if (IsKeyDown(KEY_UP)) playerVel.y = -playerSpeed;
        else if (IsKeyDown(KEY_DOWN)) playerVel.y = playerSpeed;
        else playerVel.y = 0;

        // Update the player's position
        playerPos = Vector2Add(playerPos, playerVel);

        // Clear the screen to white
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the player
        DrawCircleV(playerPos, 20, MAROON);
        EndDrawing();
    }

    // Close the window and unload all resources
    CloseWindow();

    return 0;
}
