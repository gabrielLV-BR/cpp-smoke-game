#include "./material.hpp"

StandardMaterial::StandardMaterial() : color{1, 1, 1}, maps{} {}

StandardMaterial::StandardMaterial(Color color, std::vector<Texture> maps)
    : color(color), maps(maps) {}

void StandardMaterial::bind() {
  // TODO bind
}

void StandardMaterial::unbind() {
  // TODO unbind
}