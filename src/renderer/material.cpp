#include "./material.hpp"

Material::Material(uint32_t program) : Material(program, {}, {}) {}

Material::Material(uint32_t program, std::vector<Texture> maps)
    : Material(program, maps, {}) {}

Material::Material(uint32_t program, std::vector<Texture> maps, Color color)
    : program(program), maps(maps), color(color) {}

bool Material::operator==(const Material& other) {
  return program == other.program;
}

Material::bitset Material::get_features_bitset() const {
  uint8_t bits;

  for (const auto& texture : maps)
    bits |= static_cast<uint8_t>(texture.texture_type);

  return static_cast<bitset>(bits);
}