#pragma once

#include <cstdint>
#include <vector>

#include "renderer/texture.hpp"

struct Material {
  uint32_t program;
  std::vector<Texture> maps;
};

// class Material {
//  public:
//   virtual void prepare() = 0;
//   virtual uint32_t id() const = 0;

//   bool operator==(const Material& other) { return id() == other.id(); }
// };

// class TexturedMaterial : public Material {
//  public:
//   Texture diffuse;

//   TexturedMaterial(Texture diffuse) : diffuse(diffuse) {}

//   void prepare() override {}

//   virtual uint32_t id() const override { return 0; }
// };

// template <>
// struct std::hash<Material> {
//   size_t operator()(const Material& other) {
//     return std::hash<uint32_t>()(other.id());
//   }
// };