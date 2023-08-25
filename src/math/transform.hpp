#pragma once

#include "vector.hpp"

struct Transform {
    // TODO use quaternion for rotation
    Vector3 position, scale, rotation;

    static Transform identity();
};