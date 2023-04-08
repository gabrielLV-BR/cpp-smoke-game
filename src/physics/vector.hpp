#pragma once

struct Vector3 {
  float x, y, z;

  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  bool operator==(const Vector3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }
};

struct Vector2 {
  float x, y;

  Vector2(float x, float y) : x(x), y(y) {}

  bool operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
  }
};