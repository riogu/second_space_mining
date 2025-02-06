#include "ECS.hpp"
#include "ecs_hell/component_array.hpp"
#include "ecs_hell/constants_using.hpp"
#include <cstdint>
#include <memory>
#include <string_view>

using Priority = uint64_t;

class Scheduler {
  public:
    std::array<std::string_view, MAX_SYSTEMS> system_scheduler{};
    std::set<EntityId> entities_to_delete{};
    std::set<EntityId> entities_to_add{};
};

class GlobalState {
  private:
    ECS ecs;
    Priority current_max_priority;
    Scheduler scheduler;

    void delete_scheduled() {
        for (auto entity_id : scheduler.entities_to_delete) {
            ecs.destroy_entity(entity_id);
        }
    }

  public:
    template<typename T>
    void register_system(Priority priority) {
        DEBUG_ASSERT(!scheduler.system_scheduler[priority].empty(), "already used this priority.",
                     scheduler.system_scheduler);
        scheduler.system_scheduler[priority] = ecs.register_system_ecs<T>();
        current_max_priority++;
    }
    void run_systems() {
        for (Priority curr = 0; curr < current_max_priority; curr++) {
            std::string_view type_name = scheduler.system_scheduler[curr];
            std::shared_ptr<System> system = ecs.get_system(type_name);
            system->sys_call();
        }
        delete_scheduled();
    }

    void schedule_delete(EntityId entity_id) {
        // schedule deletion for the end of the frame
        scheduler.entities_to_delete.insert(entity_id);
    }
     void schedule_add(EntityId entity_id) {
        PANIC("not implemented");
    };
};
