#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP
#include "ecs_hell/system_manager.hpp"

class PhysicsUpdate : public System {

    // plan is to kind of use this class as a way to give a better name to the
    // function call, also to group all physics updates into one known base type
    // this way they are more easily grouped later if needed
    // (this class guarantees the frametime variable in calling too)

  public:
    // float frametime;

    virtual ~PhysicsUpdate() = default;
    // NOTE: i think i dont need this anymore so i am removing this renaming
    // for now, i am using a different system of storing the functions i will use
    // virtual void update() = 0;
    // void sys_call() override { update(); };
};

class CirclePhysicsUpdate : public PhysicsUpdate {
    // an example, we deal with only the circle physics update here
    // granted, all of this could simply be one with if statements,
    // or just adding another system unrelated to physics update
    // but i want to try grouping these together for now (can remove later)

  public:
    void sys_call() override {
        update_velocity();
        detect_screen_collision();
        detect_collisions();
        update_position();
    }
    void detect_screen_collision();
    void detect_collisions();
    void detect_collision(EntityId entity_id, EntityId other_entity_id);
    void solve_collision(EntityId entity_id, EntityId other_entity_id);
    void update_velocity();
    void update_position();
};

class Draw : public System {
    // interface and abstract class to bundle up all drawing systems later
    // (kind of like an archetype?)
  public:
    virtual ~Draw() = default;
    // virtual void draw() = 0;
};

class DrawCircle : public Draw {
  private:
    // Vector2 position;
    // float radius;
    // Color color;

  public:
    // DrawCircle(Vector2 position, float radius, Color color)
    //     : position(position), radius(radius), color(color) {}
    void sys_call() override { draw(); }
    void draw();
};
#endif
