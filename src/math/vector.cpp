#include "./vector.hpp"

#include <string>
#include <unordered_map>

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

bool Vector3::operator==(const Vector3& other) const {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

inline std::string Vector3::to_string() const {
  return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ")\n";
}

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

bool Vector2::operator==(const Vector2& other) const {
  return this->x == other.x && this->y == other.y;
}