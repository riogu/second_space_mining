#include "components.hpp"
#include "ecs_hell/global_state.hpp"
#include "raymath.h"

void CirclePhysicsUpdate::update(float frametime) {
    for (auto entity_id : sys_entities) {
        auto& transform = global.get_component<Transformation>(entity_id);
        transform.position = Vector2Add(transform.position, {3.0f, 3.0f});
    }
}
