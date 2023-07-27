#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "renderer/material.hpp"
#include "renderer/mesh.hpp"

struct Model {
  std::vector<Mesh> meshes;
  std::shared_ptr<StandardMaterial> material;
};