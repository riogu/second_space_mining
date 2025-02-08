#include "ecs_hell/system_manager.hpp"
#include "raylib.h"

struct Transformation {
    Vector2 position;
    Vector2 velocity;
    float radius;
};

class PhysicsUpdate : public System {

    // plan is to kind of use this class as a way to give a better name to the
    // function call, also to group all physics updates into one known base type
    // this way they are more easily grouped later if needed
    // (this class guarantees the frametime variable in calling too)

  public:
    float frametime;

    virtual ~PhysicsUpdate() = default;
    PhysicsUpdate(float frametime) : frametime(frametime) {}

    void sys_call() override { update(frametime); };
    virtual void update(float frametime) = 0;
};

class CirclePhysicsUpdate : public PhysicsUpdate {
    // an example, we deal with only the circle physics update here
    // granted, all of this could simply be one with if statements,
    // or just adding another system unrelated to physics update
    // but i want to try grouping these together for now (can remove later)

public:
    CirclePhysicsUpdate(float frametime) : PhysicsUpdate(frametime) {}
    void update(float frametime) override;
};
