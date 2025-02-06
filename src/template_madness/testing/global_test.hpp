#include "constants.hpp"
#include "ecs_hell/ECS.hpp"
#include "ecs_hell/system_manager.hpp"
extern ECS ECS;

struct Particle {
    Vector2 position;
    Vector2 velocity;
    float radius;
};


class Physics : public System {
    void update(float frametime);

};

