#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "renderer/material.hpp"
#include "renderer/mesh.hpp"

#include "glad/glad.h"

struct Model {
  std::vector<Mesh> meshes;
  std::shared_ptr<StandardMaterial> material;
};