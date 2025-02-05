#include "ecs_hell/global_manager.hpp"
#include "raylib.h"
#include <chrono>
#include <libassert/assert.hpp>
#include "constants.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


GlobalManager global;
int main(void) {

    global.initialize();

    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
