#include "global_test.hpp"


// void create_global_manager_test() {
//     global.initialize();
//     auto entity1 = global.create_entity();
//     global.register_component<Particle>();
//     global.entity_add_component(entity1, Particle{screenCenter, Vector2{10.0f, 10.0f}});
// }



// void Physics::detect_screen_collision() {
// float damping = 0.5;
//     if (position.x + radius > screenWidth) {
//         velocity.x = -velocity.x * damping;
//         position.x = screenWidth - radius;
//     } else if (position.x - radius < 0) {
//         velocity.x = -velocity.x * damping;
//         position.x = radius;
//     } else if (position.y + radius > screenHeight) {
//         velocity.y = -velocity.y * damping;
//         position.y = screenHeight - radius;
//     } else if (position.y - radius < 0) {
//         velocity.y = -velocity.y * damping;
//         position.y = radius;
//     }
// }
