#include "./material.hpp"

StandardMaterial::StandardMaterial(Color color, std::vector<Texture> maps)
    : color(color), maps(maps) {}

void StandardMaterial::bind() {
  // TODO bind
}

void StandardMaterial::unbind() {
  // TODO unbind
}