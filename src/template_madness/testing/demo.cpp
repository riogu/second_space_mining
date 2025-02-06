#include "demo.hpp"

extern ECS ECS;

void weird_initializer() {
    ECS.register_system<DrawingSystem>();
}




void PhysicsSystem::update(float dt) {
    for (auto const& entity_id : sys_entities) {
        auto& rigidBody = ECS.entity_get_component<RigidBody>(entity_id);
        auto& transform = ECS.entity_get_component<Transformer>(entity_id);
        auto const& gravity = ECS.entity_get_component<Gravity>(entity_id);

        transform.position += Vector2Scale(rigidBody.velocity, dt);

        rigidBody.velocity += gravity.force * dt;
    }
}
void Transformer::draw() { DrawCircleV(position, radius, color); }

void DrawingSystem::draw(float frametime) {

    for (auto const entity_id : sys_entities) {




    }
}
