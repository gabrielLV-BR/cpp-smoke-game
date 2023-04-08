#pragma once

struct Vector3 {
  float x, y, z;

  Vector3() : x(0), y(0), z(0) {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  bool operator==(const Vector3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }

  union {
    float data[3];
  };
};

struct Vector2 {
  float x, y;

  Vector2() : x(0), y(0) {}
  Vector2(float x, float y) : x(x), y(y) {}

  bool operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
  }

  union {
    float data[2];
  };
};