#include "ECS.hpp"
#include "ecs_hell/component_array.hpp"
#include "ecs_hell/constants_using.hpp"
#include <memory>
#include <sched.h>
#include <string_view>
//
//--------------------------------------------------------------------------------------
//

using Priority = uint64_t;

class Scheduler {
  public:
    std::array<std::shared_ptr<System>, MAX_SYSTEMS> system_scheduler{};

    // Array of component_masks where the index corresponds to the entity ID
    // used to delay updates to the end of each frame
    // std::set<EntityId> entities_to_create{};
    // std::set<EntityId> entities_to_destroy{};
    // each entityId corresponds to an index on this array
    // std::set<EntityId> entities_to_update_components{};
    // std::array<ComponentMask, MAX_ENTITY_IDS> scheduled_entity_component_masks{};
    // NOTE: i have concluded that there isnt a real need to schedule these changes
    // to the end of the frame. i can still do this, but i feel it adds little benefit
    // as we might want to create systems that depend on some of these changes
    // plus its not even necessarily more efficient as shared state is still required
};

class GlobalState {

    // only missing separating systems from the entities and components
    // and running all the systems at the end
    // but i think as long as i dont touch the systems, they dont communicate with EC
    // part so it should be trivial?

  private:
    std::unique_ptr<ECS> ecs;
    Priority current_max_priority{0};
    Scheduler scheduler{};
    std::array<EntityId, MAX_ENTITY_IDS> all_entity_ids_debug{};

  public:
    void initialize() {
        ecs = std::make_unique<ECS>();
        ecs->initialize();
    }
    // --------------------------------------------------------------------------------------
    // entity stuff
    [[nodiscard]] EntityId create_entity() {
        // added "scheduled" to allude to the fact this action only happens by
        // the end of the frame, can remove later
        EntityId entity_id = ecs->create_entity();
        // scheduler.entities_to_create.insert(entity_id);
        all_entity_ids_debug[entity_id] = entity_id;
        return entity_id;
    };

    void destroy_entity(EntityId entity_id) {
        // schedule deletion for the end of the frame
        // scheduler.entities_to_destroy.insert(entity_id);
        ecs->destroy_entity(entity_id);
        all_entity_ids_debug[entity_id] = -1;
    }
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // component stuff
    template<typename T>
    void register_component() {
        ecs->register_component<T>();
    }
    template<typename T>
    void entity_add_component(EntityId entity_id, T component) {
        // scheduler.scheduled_entity_component_masks[entity_id] =

        ecs->entity_add_component(entity_id, component);
    }
    template<typename T> // remove from entity
    void entity_remove_component(EntityId entity_id) {
        // scheduler.scheduled_entity_component_masks[entity_id] =
        ecs->entity_remove_component<T>(entity_id);
    }
    template<typename T>
    [[nodiscard]] T& get_component(EntityId entity_id) {
        return ecs->get_component<T>(entity_id);
    }
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // system stuff
    template<typename T, Priority priority, typename... Types>
    void register_system(ComponentMask component_mask, const Types&... args) {
        DEBUG_ASSERT(scheduler.system_scheduler[priority] == nullptr,
                     "already used this priority.", scheduler.system_scheduler);

        std::shared_ptr<System> system_ptr = std::make_shared<T>(args...);

        ecs->register_system<T>(component_mask, system_ptr);

        scheduler.system_scheduler[priority] = system_ptr;
        current_max_priority++;
    }
    template<typename T>
    void add_system_instance(T system) {}
    // void notify_systems() {
    //     for (auto entity_id : scheduler.entities_to_update_components) {
    //     }
    // }
    void run_systems() {
        for (Priority curr = 0; curr < current_max_priority; curr++) {
            // std::string_view type_name = scheduler.system_scheduler[curr];
            // std::shared_ptr<System> system = ecs->get_system(type_name);
            // system->sys_call();
        }
    }

    // --------------------------------------------------------------------------------------
};

// NOTE: we are linking this global variable with all files that include this
// header
extern GlobalState global;
