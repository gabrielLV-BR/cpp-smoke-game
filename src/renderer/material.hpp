#pragma once

#include <cstdint>
#include <vector>
#include <bitset>

#include "renderer/texture.hpp"
#include "utils/color.hpp"

class Material {
 private:
  static uint32_t LAST_INDEX;
  uint32_t id;

  using bitset = std::bitset<8>;

 public:
  uint32_t program;
  Color color;
  std::vector<Texture> maps;

  bitset map_bitset;

  Material(uint32_t program);
  Material(uint32_t program, std::vector<Texture> maps);
  Material(uint32_t program, std::vector<Texture> maps, Color color);

  bool operator==(const Material& other);

  inline uint32_t id() const { return id; }

 private:
  bitset calculate_bitset() const {
    uint8_t bits;

    for (const auto& texture : maps)
      bits |= static_cast<uint8_t>(texture.texture_type);

    return static_cast<bitset>(bits);
  }
};