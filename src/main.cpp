#include "ecs_hell/ECS.hpp"
#include "raylib.h"
#include <libassert/assert.hpp>
#include "constants.hpp"
#include "ecs_hell/world.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
GlobalState global;

int main(void) {


    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");

    while (!WindowShouldClose()) {
        BeginDrawing();
        float frametime = GetFrameTime();


        ClearBackground(BLACK);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
