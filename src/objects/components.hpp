#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP
#include "raylib.h"

struct Body {
    Vector2 position;
    Vector2 velocity;
    float mass;
};

// NOTE: due to how we made the component arrays
// we cant add structs that cant use default initializer lists
// so, i cant make a Shape interface for other components to inherit from
// a workaround to this is keeping these constructors in GlobalState if you want
// to use user defined constructors but, you still cant store the structs as Shape
// pointers
// TODO: (try seeing if you can change ComponentArray to support this kind of thing?)
// struct Shape {
//     // generic interface for shapes, not sure if ill use it but its easy
//     // to remove later
//     virtual ~Shape() = default;
// };

struct CircleShape {
    float radius;
};

struct Render {
    Color color;
};
#endif
