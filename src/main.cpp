#include "ecs_hell/global_manager.hpp"
#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
GlobalManager global;
int main(void) {
    const int screenWidth = 500;
    const int screenHeight = 500;

    global.initialize();
    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
