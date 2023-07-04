#pragma once

#include <cstdint>
#include <vector>
#include <bitset>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

enum MaterialMapIndex { DIFFUSE = 0, NORMAL = 1 };

class Material {
 public:
  using bitset = std::bitset<8>;

 private:
  static uint32_t LAST_INDEX;
  uint32_t id;

 public:
  uint32_t program;
  Color color;
  std::vector<Texture> maps;

  Material(uint32_t program);
  Material(uint32_t program, std::vector<Texture> maps);
  Material(uint32_t program, std::vector<Texture> maps, Color color);

  bool operator==(const Material& other);

  inline uint32_t id() const { return id; }
};