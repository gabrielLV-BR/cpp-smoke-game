#pragma once

#include <unordered_map>

struct Vector3 {
  float x, y, z;

  Vector3() : x(0), y(0), z(0) {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  bool operator==(const Vector3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }

  std::string to_string() const {
    return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
           std::to_string(z) + ")\n";
  }

  std::size_t hash() const {
    using std::hash;
    return hash<float>()(x) ^ hash<float>()(y) ^ hash<float>()(z);
  }
};

struct Vector2 {
  float x, y;

  Vector2() : x(0), y(0) {}
  Vector2(float x, float y) : x(x), y(y) {}

  bool operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
  }

  std::size_t hash() const {
    using std::hash;
    return hash<float>()(x) ^ hash<float>()(y);
  }
};