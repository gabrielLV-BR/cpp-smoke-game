#pragma once

#include <cstdint>

class Material {
 public:
  virtual void prepare() = 0;
  virtual uint32_t id() const = 0;

  bool operator==(const Material& other) { return id() == other.id(); }
};

class TexturedMaterial : public Material {
 public:
  TexturedMaterial() {}

  void prepare() override {}
  virtual uint32_t id() const override { return 0; }
};

template <>
struct std::hash<Material> {
  size_t operator()(const Material& other) {
    return std::hash<uint32_t>()(other.id());
  }
};