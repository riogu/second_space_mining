#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP
#include "constants_using.hpp"
#include "ecs_hell/component_array.hpp"
#include <array>
#include <libassert/assert.hpp>
#include <cstdint>
#include <queue>
// Entities are represented by unique IDs

class EntityManager {
  private:
    uint64_t living_entity_count{};
    std::queue<EntityId> available_entity_ids{};
    // Array of component_masks where the index corresponds to the entity ID
    std::array<ComponentMask, MAX_ENTITY_IDS> entity_component_masks{};

  public:
    EntityManager() {
        for (EntityId entity_id = 0; entity_id < MAX_ENTITY_IDS; entity_id++) {
            available_entity_ids.push(entity_id);
        }
    }
    EntityId create_entity() {
        DEBUG_ASSERT(living_entity_count < MAX_ENTITY_IDS , "too many living entities", living_entity_count);
        EntityId id = available_entity_ids.front();
        available_entity_ids.pop();
        return id;
    }
    void destroy_entity(EntityId entity_id) {
        DEBUG_ASSERT(entity_id < MAX_ENTITY_IDS , "exceeded MAX_ENTITY_IDS");
        // reset this entity component
        entity_component_masks[entity_id] = 0;

        // add the id again to be reused later
        available_entity_ids.push(entity_id);
        living_entity_count--;
    }
    // NOTE: entity manager is *NOT* responsible for changing component_masks
    void add_to_component_mask(EntityId entity_id, ComponentId component_id) {
        DEBUG_ASSERT(living_entity_count < MAX_ENTITY_IDS , "too many living entities");
        DEBUG_ASSERT(entity_id < MAX_ENTITY_IDS , "exceeded MAX_ENTITY_IDS");
        entity_component_masks[entity_id] |= 1 << component_id;
    }
    void remove_from_component_mask(EntityId entity_id, ComponentId component_id) {
        DEBUG_ASSERT(living_entity_count < MAX_ENTITY_IDS , "too many living entities");
        DEBUG_ASSERT(entity_id < MAX_ENTITY_IDS , "exceeded MAX_ENTITY_IDS");
        // XOR makes it so if both bits are 1 then it turns into a 0,
        DEBUG_ASSERT(entity_component_masks[entity_id] && component_id == 0,
                     "component wasn't in the mask", entity_component_masks[entity_id]);
        // FIXME: make sure that this works as intended (test removing components later)
        entity_component_masks[entity_id] ^= 1 << component_id;
    }
    [[nodiscard]] ComponentMask get_component_mask(EntityId entity_id) {
        DEBUG_ASSERT(entity_id < MAX_ENTITY_IDS, "exceeded MAX_ENTITY_IDS");
        return entity_component_masks[entity_id];
    }
};
#endif
