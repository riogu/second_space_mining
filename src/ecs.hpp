#include "raylib.h"
#include <array>
#include <cassert>
#include <cstdint>
#include <queue>

// Entities are represented by unique IDs
using EntityId = uint64_t;
const EntityId MAX_ENTITY_IDS = 5000;

// components also have ids
using ComponentId = uint8_t;
const ComponentId MAX_COMPONENTS = 64;

using ComponentMask = uint64_t;

struct Location {
    Vector2 position;
    // Vector3 rotation;
};
struct Movement {
    Vector2 initialVelocity;
    Vector2 velocity;
};

class EntityManager {
  private:
    uint64_t living_entity_count;
    std::queue<EntityId> available_entity_ids;
	// Array of component_masks where the index corresponds to the entity ID
    std::array<ComponentMask, MAX_ENTITY_IDS> entity_component_masks;

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
    void set_component_mask(EntityId entity_id, ComponentMask component_mask) {
        assert(living_entity_count < MAX_ENTITY_IDS && "exceeded MAX_ENTITY_IDS");
        assert(entity_id < MAX_ENTITY_IDS && "exceeded MAX_ENTITY_IDS");
        entity_component_masks[entity_id] = component_mask;
    }
    ComponentMask get_component_mask(EntityId entity_id) {
        return entity_component_masks[entity_id];
    }
};
