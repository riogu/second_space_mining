#include "ecs_hell/global_manager.hpp"
#include "raylib.h"
#include <libassert/assert.hpp>
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
    std::vector<int> vec;
    vec.push_back(123123);

    // int asdasd = ASSERT_VAL(vec);


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
