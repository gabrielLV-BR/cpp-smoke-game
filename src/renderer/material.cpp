#include "./material.hpp"

Material::Material(uint32_t program) : Material(program, {}, {}) {}

Material::Material(uint32_t program, std::vector<Texture> maps)
    : Material(program, maps, {}) {}

Material::Material(uint32_t program, std::vector<Texture> maps, Color color)
    : program(program), maps(maps), color(color) {}

bool Material::operator==(const Material& other) {
  return program == other.program;
}