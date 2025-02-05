#include <libassert/assert.hpp>
#include "ecs/component_array.hpp"
#include "raylib.h"
#include <array>
#include <vector>
// #include "ecs.hpp"
/*
cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=On
cmake --build build
*/
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    const int screenWidth = 500;
    const int screenHeight = 500;

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
