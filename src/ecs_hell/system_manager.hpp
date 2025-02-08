#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP
#include "constants_using.hpp"
#include <cstdlib>
#include <libassert/assert.hpp>
#include <memory>
#include <set>
#include <string_view>
#include <unordered_map>

class System {
    // all systems should inherit from this system

  public:
    std::set<EntityId> sys_entities{};
    // sys_call is a generic method, required to sort systems by priority at the end.
    // it is necessary to work around this method by storing variables in the system
    // if needed for subsequent function calls
    virtual void sys_call() = 0;
};

class SystemManager {
  private:
    // convert t_name -> respective component mask
    // simple map implementation, no need for premature optimization
    std::unordered_map<std::string_view, ComponentMask> system_component_masks;
    // t_name -> respective System pointer
    std::unordered_map<std::string_view, std::shared_ptr<System>> all_systems;

  public:
    template<typename T>
    void register_system(const ComponentMask& component_mask,
                    const std::shared_ptr<System>& system_ptr) {
        std::string_view t_name = libassert::type_name<T>();
        DEBUG_ASSERT(!all_systems.contains(t_name), "registered the system twice.",
                     all_systems);
        all_systems.insert({t_name, system_ptr});

        set_component_mask<T>(component_mask);
    }

  private:
    template<typename T>
    void set_component_mask(ComponentMask component_mask) {
        std::string_view t_name = libassert::type_name<T>();
        DEBUG_ASSERT(all_systems.contains(t_name),
                     "tried using system without registering!", all_systems);
        system_component_masks.insert({t_name, component_mask});
    }

  public:
    // TODO: maybe remove these extra public private later

    std::shared_ptr<System> get_system(std::string_view t_name) {
        return all_systems[t_name];
    }
    // template<typename T> // will i use this? not sure (consider deleting)
    // void change_component_mask(ComponentMask component_mask) {
    //     std::string_view t_name = typeid(T).name();
    //     DEBUG_ASSERT(!all_systems.contains(t_name), "tried using system without
    //     registering!",
    //                  all_systems);
    //     system_component_masks[t_name] = component_mask;
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
            auto const& t_name = pair.first;
            auto const& system = pair.second;
            auto const& system_mask = system_component_masks[t_name];

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
