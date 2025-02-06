#include "ecs_hell/ECS.hpp"
#include "raylib.h"
#include "raymath.h"
struct Gravity {
    Vector2 force;
};

struct RigidBody {
    Vector2 velocity;
    Vector2 acceleration;
};

struct Transformer {
    Vector2 position;
    Vector2 rotation;
    float radius;
    Color color;
    void draw();
};

class PhysicsSystem : public System {
    void update(float frametime);
};

class DrawingSystem : public System {
    void draw(float frametime);
};
