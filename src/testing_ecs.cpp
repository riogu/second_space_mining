#include "constants.hpp"
#include "ecs_hell/constants_using.hpp"
#include "ecs_hell/global_state.hpp"
#include "objects/components.hpp"
#include "objects/systems.hpp"
EntityId create_celestial_body(float radius, float mass, Vector2 velocity,
                               Vector2 position, Color color);
void make_lots_of_entities_test();
void ecs_test() {
    // TODO: add functions for system component_masks changes
    global.register_component<Body>();
    global.register_component<Render>();
    global.register_component<CircleShape>();
    ComponentMask component_mask = 0b000111;
    global.register_system<CirclePhysicsUpdate, 0>(component_mask);
    component_mask = 0b000111;
    global.register_system<class DrawCircle, 1>(component_mask);


    EntityId entity_id = global.create_entity();

    make_lots_of_entities_test();

    // cant register the systems effectively until ive made a system
    // that allows me to pass to them the variables i want for their function.
    // this means that a good solution is treating them the same as components
    // and require an initialization like a component requires
    // and i will now copy over the components code for systems
    // and then maybe later we can make system entities and separate both logics
    // and have a nice finished system.
}
void make_lots_of_entities_test() {
    create_celestial_body(10, 6000, {0, 140},
                          {screenWidth / 2.0f, 3.0f * screenHeight / 4.0f}, ORANGE);
    create_celestial_body(24, 60000, {0, 140}, {screenWidth / 4.0f, screenHeight / 2.0f},
                          BLUE);
    create_celestial_body(50, 6000000, {100, 140},
                          {3.0f * screenWidth / 4.0f, screenHeight / 2.0f}, GREEN);
    create_celestial_body(100, 89000000, {0, 0}, screenCenter, RED);
}

EntityId create_celestial_body(float radius, float mass, Vector2 velocity,
                               Vector2 position, Color color) {
    EntityId entity_id = global.create_entity();
    global.entity_add_component(
        entity_id, Body{.position = screenCenter, .velocity = velocity, .mass = mass});
    global.entity_add_component(entity_id, Render{.color = color});
    global.entity_add_component(entity_id, CircleShape{.radius = radius});
    return entity_id;
}
