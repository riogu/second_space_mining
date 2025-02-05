#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP
#include "component_array.hpp"
#include "constants_using.hpp"
#include "ecs_hell/entity_manager.hpp"
#include <memory>
#include <string_view>

#endif

class ComponentManager {

  private:
    // each type needs to map to a respective id
    // NOTE: (components are never removed in this implementation)
    std::unordered_map<std::string_view, ComponentId> component_ids;
    std::unordered_map<std::string_view, std::shared_ptr<IComponentArray>> component_arrays;
    ComponentId current_component_id{};

  public:
    template<typename T>
    void register_component() {
        std::string_view type_name = typeid(T).name();
        DEBUG_ASSERT(!component_ids.contains(type_name), "already added this component",
                     component_ids);
        // assign the name a unique id (used for the component bitmasks)
        component_ids.insert({type_name, current_component_id});

        // use the type_name also for creating a new array of this component
        component_arrays({current_component_id, std::make_shared<ComponentArray<T>>()});

        current_component_id++;
    }
    template<typename T>
    ComponentId get_component_id() {
        const char* type_name = typeid(T).name();
        DEBUG_ASSERT(component_ids.contains(type_name), "forgot to register component",
                     component_ids);
        // we use this component id to make component bitmasks
        return component_ids[type_name];
    }
    template<typename T>
    T& get_component(EntityId entity_id) {
        const char* type_name = typeid(T).name();
        DEBUG_ASSERT(component_ids.contains(type_name), "forgot to register component",
                     component_ids);
        ComponentArray<T> cast_component_array =
            std::static_pointer_cast<ComponentArray<T>>(component_arrays[type_name]);
        return cast_component_array.get_component_data(entity_id);
    }

    // responible for changing the component mask of the entity
    template<typename T>
    void add_component(EntityId entity_id, T component) {
        const char* type_name = typeid(T).name();
        DEBUG_ASSERT(component_ids.contains(type_name), "forgot to register component",
                     component_ids);
        // we now cast away from our interface into our **known** type conversion
        // much better than when i was using dynamic_cast<> to find out what the type of the
        // interface was
        ComponentArray<T> cast_component_array =
            std::static_pointer_cast<ComponentArray<T>>(component_arrays[type_name]);

        cast_component_array.add_component_data(entity_id, component);
    }
    // responible for changing the component mask of the entity
    template<typename T>
    void remove_component(EntityId entity_id) {

        std::string_view type_name = typeid(T).name();
        DEBUG_ASSERT(component_ids.contains(type_name), "forgot to register component",
                     component_ids);

        ComponentArray<T> cast_component_array =
            std::static_pointer_cast<ComponentArray<T>>(component_arrays[type_name]);
        cast_component_array.remove_component_data(entity_id);
    }
    void clear_destroyed_entity(EntityId entity_id) {
        // erases destroyed entity from all sets
        for (auto const& pair : component_arrays) {
            auto const& component_array = pair.second;
            // notice we can erase even if the element wasnt there
            // (simplifying the implementation so i dont go insane)
            component_array->entity_destroyed(entity_id);
        }
    }
};
