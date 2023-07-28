#pragma once

#include <unordered_map>
#include "math/vector.hpp"

struct Color {
  float r, g, b;

  Color();
  Color(float r, float g, float b);

  union {
    float array[3];
  };

  union {
    Vector3 vec;
  };

  bool operator==(const Color& c) const {
    return r == c.r && g == c.g && b == c.b;
  }
};

template <>
struct std::hash<Color> {
  size_t operator()(const Color& c) const {
    return std::hash<float>()(c.r) ^ std::hash<float>()(c.g) ^
           std::hash<float>()(c.b);
  }
};