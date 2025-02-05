#ifndef GLOBAL_MANAGER_HPP
#define GLOBAL_MANAGER_HPP

#include "ecs_hell/component_manager.hpp"
#include "ecs_hell/constants_using.hpp"
#include "ecs_hell/entity_manager.hpp"
#include "ecs_hell/system_manager.hpp"
#include <memory>

class GlobalManager {
  private:
    std::unique_ptr<ComponentManager> component_manager;
    std::unique_ptr<EntityManager> entity_manager;
    std::unique_ptr<SystemManager> system_manager;

  public:
    // NOTE: possibly change this into a wrapper around entities so we can can call:
    // entity.add_component(component);

    void initialize() {
        component_manager = std::make_unique<ComponentManager>();
        entity_manager = std::make_unique<EntityManager>();
        system_manager = std::make_unique<SystemManager>();
    }
    // --------------------------------------------------------------------------------------
    // entity stuff
    EntityId create_entity() { return entity_manager->create_entity(); }

    void destroy_entity(EntityId entity_id) {
        entity_manager->destroy_entity(entity_id);
        component_manager->clear_destroyed_entity(entity_id);
        system_manager->clear_destroyed_entity(entity_id);
    }
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // component stuff
    template<typename T>
    void register_component() {
        component_manager->register_component<T>();
    }

    template<typename T>
    void entity_add_component(EntityId entity_id, T component) {
        // tell the component manager to add this entity_id associated to this component
        // this updates the entity's component mask
        component_manager->add_component<T>(entity_id, component);
        // update the entity_id's mask
        auto component_mask = entity_manager->get_component_mask(entity_id);
        entity_manager->set_component_mask(entity_id, component_mask);
        // notify the systems of the change
        system_manager->entity_component_mask_changed(entity_id, component_mask);
    }

    template<typename T> // remove from entity
    void entity_remove_component(EntityId entity_id) {
        component_manager->remove_component<T>(entity_id);

        ComponentMask component_mask = entity_manager->get_component_mask(entity_id);
        entity_manager->set_component_mask(entity_id, component_mask);
        system_manager->entity_component_mask_changed(entity_id, component_mask);
    }

    template<typename T>
    T& entity_get_component(EntityId entity_id) {
        return component_manager->get_component<T>(entity_id);
    }

    template<typename T>
    ComponentId get_component_id() {
        return component_manager->get_component_id<T>();
    }
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // system stuff
    template<typename T>
    std::shared_ptr<T> register_system() {
        return system_manager->register_system<T>();
    }

    template<typename T>
    void set_system_component_mask(ComponentMask component_mask) {
        system_manager->set_component_mask<T>(component_mask);
    }
    // --------------------------------------------------------------------------------------
};

#endif
