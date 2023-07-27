#pragma once

#include <cstdint>
#include <vector>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

class StandardMaterial {
 private:
  uint32_t _id;

 public:
  Color color;
  // textures for different maps, the position of the texture indicates what
  // map it is to be used for

  StandardMaterial() : _id(0) {
    static uint32_t LAST_INDEX = 0;
    _id = LAST_INDEX++;
  }

  bool operator==(const StandardMaterial& other) const {
    return program == other.program && color == other.color;
  }

  inline uint32_t id() const { return _id; }
};

template <>
struct std::hash<StandardMaterial> {
  size_t operator()(const StandardMaterial& mat) const {
    return std::hash<uint32_t>()(mat.id());
  }
};