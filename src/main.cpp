#include "ecs_hell/ECS.hpp"
#include "raylib.h"
#include <libassert/assert.hpp>
#include "constants.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

ECS ECS;


int main(void) {
    ECS.initialize();


    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");

    while (!WindowShouldClose()) {
        BeginDrawing();
        float frametime = GetFrameTime();

        PhysicsSystem.update(frametime);

        ClearBackground(BLACK);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
