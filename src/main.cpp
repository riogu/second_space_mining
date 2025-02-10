#include "constants.hpp"
#include "ecs_hell/constants_using.hpp"
#include "ecs_hell/global_state.hpp"
#include "objects/systems.hpp"
#include "raylib.h"
#include <memory>
#include <mutex>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
std::unique_ptr<GlobalState> global;
void ecs_test();
void add_an_entity();
int main(void) {

    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");
    global = std::make_unique<GlobalState>();
    global->initialize();

    SetTargetFPS(60);
    ecs_test();
    int count = 0;
    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        global->frametime = GetFrameTime();
        global->run_systems();

        count++;
        if (60 == count % 120) {
            add_an_entity();
        }


        ClearBackground(BLACK);
        EndDrawing();
    }
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}




