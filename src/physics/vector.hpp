#pragma once

#include <unordered_map>

struct Vector3 {
  float x, y, z;

  Vector3() : x(0), y(0), z(0) {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  bool operator==(const Vector3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }

  inline std::string to_string() const {
    return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
           std::to_string(z) + ")\n";
  }
};

struct Vector2 {
  float x, y;

  Vector2() : x(0), y(0) {}
  Vector2(float x, float y) : x(x), y(y) {}

  bool operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
  }
};

template <>
struct std::hash<Vector3> {
  size_t operator()(const Vector3& v) {
    return hash<float>()(v.x) ^ hash<float>()(v.y) ^ hash<float>()(v.z);
  }
};

template <>
struct std::hash<Vector2> {
  size_t operator()(const Vector2& v) {
    return hash<float>()(v.x) ^ hash<float>()(v.y);
  }
};