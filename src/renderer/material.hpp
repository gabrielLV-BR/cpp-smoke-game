#pragma once

#include <cstdint>
#include <vector>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

struct Material {
  static const uint32_t DIFFUSE_MAP;
  static const uint32_t NORMAL_MAP;

 private:
  static uint32_t LAST_INDEX;
  uint32_t id;

 public:
  uint32_t program;
  Color color;
  std::vector<Texture> maps;

  Material() : id(LAST_INDEX++) {}

  bool operator==(const Material& other) {
    return program == other.program && color == other.color;
  }

  inline uint32_t id() const { return id; }
};

uint32_t Material::LAST_INDEX = 0;

template <>
struct std::hash<Material> {
  size_t operator()(const Material& mat) {
    return std::hash<uint32_t>()(mat.id());
  }
};