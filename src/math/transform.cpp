#include "transform.hpp"

Transform Transform::identity() {
    return Transform{
        .position = Vector3(0, 0, 0),
        .scale = Vector3(1, 1, 1),
        .rotation = Vector3(0, 0, 0)};
}