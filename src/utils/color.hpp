#pragma once

#include "physics/vector.hpp"

struct Color {
  float x, y, z;

  union {
    float array[3];
  };

  union {
    Vector3 vec;
  };
};