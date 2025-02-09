#include "constants.hpp"
#include "ecs_hell/global_state.hpp"
#include "objects/components.hpp"
#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
GlobalState global;
void ecs_test();

void system_test_ecs();
int main(void) {
    SetTraceLogLevel(DEBUG);

    global.initialize();

    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");

    // auto circle_physics_update = global.get_system<CirclePhysicsUpdate>();
    // auto draw_circle = global.get_system<class DrawCircle>();


    ecs_test();

    while (!WindowShouldClose()) {
        BeginDrawing();
        static float frametime = GetFrameTime();

        // circle_physics_update->update();
        // draw_circle->draw();
        // DrawCircleV(screenCenter, 10.0f, BLUE);
        global.frametime = GetFrameTime();
        global.run_systems();

        ClearBackground(BLACK);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
