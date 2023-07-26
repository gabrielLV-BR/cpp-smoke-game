#pragma once

#include <cstdint>
#include <vector>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

struct Material {
  static const uint32_t DIFFUSE_MAP;
  static const uint32_t NORMAL_MAP;

 private:
  uint32_t _id;

 public:
  uint32_t program;
  Color color;
  std::vector<Texture> maps;

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
};