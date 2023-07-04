#pragma once

#include <cstdint>
#include <vector>
#include <bitset>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

enum MaterialFeaturesBits { DIFFUSE = 1 << 0, NORMAL = 1 << 1 };

class BaseMaterial {
 public:
  using bitset = std::bitset<8>;

 private:
  static uint32_t LAST_INDEX;
  uint32_t id;

 public:
  uint32_t program;
  Color color;

  BaseMaterial();

  void bind();
  void unbind();

  inline uint32_t id() const { return id; }

 protected:
  BaseMaterial(uint32_t program);
};