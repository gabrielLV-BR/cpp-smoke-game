#pragma once

#include <cstdint>
#include <vector>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

class StandardMaterial {
 private:
  // handle to the program of this Material's shader
  uint32_t program;

 public:
  Color color;
  // textures for different maps, the position of the texture indicates what
  // map it is to be used for

  // 0 - Diffuse
  // 1 - Normal
  // TODO allow for more maps
  std::vector<Texture> maps;

  StandardMaterial();
  StandardMaterial(Color color, std::vector<Texture> maps);

  void bind();
  void unbind();
};