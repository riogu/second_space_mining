#ifndef CONSTANTS_USING_HPP
#define CONSTANTS_USING_HPP
#include <cstdint>
using EntityId = uint64_t;
const EntityId MAX_ENTITY_IDS = 1000;

// components also have ids
using ComponentId = uint8_t;
const ComponentId MAX_COMPONENTS = 64;

using ComponentMask = uint64_t;


const uint64_t MAX_SYSTEMS = 12;

#endif
