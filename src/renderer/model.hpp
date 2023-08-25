#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "renderer/mesh.hpp"
#include "math/transform.hpp"

struct Model {
    std::vector<Mesh> meshes;
    Transform transform;
};