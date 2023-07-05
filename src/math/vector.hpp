#pragma once

#include <string>
#include <unordered_map>

struct Vector3 {
  float x, y, z;

  Vector3();
  Vector3(float x, float y, float z);

  bool operator==(const Vector3& other) const;

  inline std::string to_string() const;
};

struct Vector2 {
  float x, y;

  Vector2();
  Vector2(float x, float y);

  bool operator==(const Vector2& other) const;
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