#include "constants.hpp"
#include "ecs_hell/constants_using.hpp"
#include "ecs_hell/global_state.hpp"
#include "objects/components.hpp"
#include "raylib.h"
#include <libassert/assert.hpp>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
GlobalState global;

void ecs_test(float frametime);
int main(void) {

    global.initialize();
    float frametime = GetFrameTime();
    ecs_test(frametime);
    InitWindow(screenWidth, screenHeight, "THIS... is a BUCKET.");

    while (!WindowShouldClose()) {
        BeginDrawing();

        float frametime = GetFrameTime();
        global.run_systems();
        ClearBackground(BLACK);

        EndDrawing();
    }

    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void ecs_test(float frametime) {
    EntityId entity_id = global.create_entity();
    global.register_component<Transformation>();
    global.entity_add_component(entity_id,
                                Transformation(screenCenter, {0.0f, 0.0f}, 10.0f));
    ComponentMask component_mask = 1 << 1;
    // cant register the systems effectively until ive made a system
    // that allows me to pass to them the variables i want for their function.
    // this means that a good solution is treating them the same as components
    // and require an initialization like a component requires
    // and i will now copy over the components code for systems
    // and then maybe later we can make system entities and separate both logics
    // and have a nice finished system.
    // CirclePhysicsUpdate circle_update = CirclePhysicsUpdate(frametime);
    global.register_system<CirclePhysicsUpdate, 0>(component_mask, frametime);
    // global.add_system_instance(circle_update);
}
