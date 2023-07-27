#pragma once

#include <cstdint>
#include <vector>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

class StandardMaterial {
 private:
<<<<<<< HEAD
  // handle to the program of this Material's shader
  uint32_t program;
=======
  uint32_t _id;
>>>>>>> d27f141ba1857a353d8e1b7469aa15d3daff0602

 public:
  Color color;
  // textures for different maps, the position of the texture indicates what
  // map it is to be used for

<<<<<<< HEAD
  // 0 - Diffuse
  // 1 - Normal
  // TODO allow for more maps
  std::vector<Texture> maps;

  StandardMaterial();
  StandardMaterial(Color color, std::vector<Texture> maps);

  void bind();
  void unbind();
=======
  Material() : _id(0) {
    static uint32_t LAST_INDEX = 0;
    _id = LAST_INDEX++;
  }

  bool operator==(const Material& other) const {
    return program == other.program && color == other.color;
  }

  inline uint32_t id() const { return _id; }
};

template <>
struct std::hash<Material> {
  size_t operator()(const Material& mat) const {
    return std::hash<uint32_t>()(mat.id());
  }
>>>>>>> d27f141ba1857a353d8e1b7469aa15d3daff0602
};