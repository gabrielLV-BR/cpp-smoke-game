#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "renderer/mesh.hpp"

#include "glad/glad.h"

struct Model {
  std::vector<Mesh> meshes;
  // TODO std::shared_ptr<Material> material;
};