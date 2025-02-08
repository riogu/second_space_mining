#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP
#include "constants_using.hpp"
#include <libassert/assert.hpp>
#include <memory>
#include <set>
#include <string_view>
#include <unordered_map>

class System {
    // all systems should inherit from this system

  public:
    std::set<EntityId> sys_entities{};
    virtual void sys_call() = 0;
};

class SystemManager {
  private:
    // convert type_name -> respective component mask
    // simple map implementation, no need for premature optimization
    std::unordered_map<std::string_view, ComponentMask> system_component_masks;
    // type_name -> respective System pointer
    std::unordered_map<std::string_view, std::shared_ptr<System>> all_systems;

  public:
    template<typename T>
    std::string_view register_system(ComponentMask component_mask) {
        std::string_view type_name = typeid(T).name();
        DEBUG_ASSERT(!all_systems.contains(type_name), "registered the system twice.",
                     all_systems);
        auto system = std::make_shared<T>();
        all_systems.insert({type_name, system});
        set_component_mask<T>(component_mask);
        return type_name;
    }

  private:
    template<typename T>
    void set_component_mask(ComponentMask component_mask) {
        std::string_view type_name = typeid(T).name();
        DEBUG_ASSERT(all_systems.contains(type_name),
                     "tried using system without registering!", all_systems);
        system_component_masks.insert({type_name, component_mask});
    }

  public:
    // TODO: maybe remove these extra public private later

    std::shared_ptr<System> get_system(std::string_view type_name) {
        return all_systems[type_name];
    }
    // template<typename T> // will i use this? not sure (consider deleting)
    // void change_component_mask(ComponentMask component_mask) {
    //     std::string_view type_name = typeid(T).name();
    //     DEBUG_ASSERT(!all_systems.contains(type_name), "tried using system without
    //     registering!",
    //                  all_systems);
    //     system_component_masks[type_name] = component_mask;
    // }
    void notify_destroyed_entity(EntityId entity_id) {
        // erases destroyed entity from all sets
        // std::set requires no checks
        for (auto const& pair : all_systems) {
            auto const& system = pair.second;
            // notice we can erase even if the element wasnt there
            // (simplifying the implementation so i dont go insane)
            system->sys_entities.erase(entity_id);
        }
    }
    void entity_component_mask_changed(EntityId entity_id, ComponentMask component_mask) {
        // notify all systems that the entity has been destroyed
        // and if matching, add this entity to the system
        for (auto const& pair : all_systems) {
            auto const& type_name = pair.first;
            auto const& system = pair.second;
            auto const& system_mask = system_component_masks[type_name];

            if ((component_mask & system_mask) == system_mask) {
                // NOTE: (see unity EntityQuery)
                // TODO: add **variations** of system component_masks:
                // requires implementing archetypes before this though
                // >All
                // >Any
                // >none
                system->sys_entities.insert(entity_id);
            } else {
                system->sys_entities.erase(entity_id);
            }
        }
    }
};
#endif
