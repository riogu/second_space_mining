#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP
#include "constants_using.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <queue>
// Entities are represented by unique IDs


class EntityManager {
  private:
    uint64_t living_entity_count{};
    std::queue<EntityId> available_entity_ids;
    // Array of component_masks where the index corresponds to the entity ID
    std::array<ComponentMask, MAX_ENTITY_IDS> entity_component_masks{};

  public:
    EntityManager() {
        for (EntityId entity_id = 0; entity_id < MAX_ENTITY_IDS; entity_id++) {
            available_entity_ids.push(entity_id);
        }
    }
    EntityId create_entity() {
        assert(living_entity_count < MAX_ENTITY_IDS && "exceeded MAX_ENTITY_IDS");
        EntityId id = available_entity_ids.front();
        available_entity_ids.pop();
        return id;
    }
    void destroy_entity(EntityId entity_id) {
        assert(entity_id < MAX_ENTITY_IDS && "exceeded MAX_ENTITY_IDS");
        // reset this entity component
        entity_component_masks[entity_id] = 0;

        // add the id again to be reused later
        available_entity_ids.push(entity_id);
        living_entity_count--;
    }
    // NOTE: entity manager is *NOT* responsible for changing component_masks
    void add_to_component_mask(EntityId entity_id,ComponentId component_id) {
        assert(living_entity_count < MAX_ENTITY_IDS && "too many living entities");
        assert(entity_id < MAX_ENTITY_IDS && "exceeded MAX_ENTITY_IDS");
        entity_component_masks[entity_id] |= 1 << component_id;
    }
    ComponentMask get_component_mask(EntityId entity_id) {
        return entity_component_masks[entity_id];
    }

};
#endif
