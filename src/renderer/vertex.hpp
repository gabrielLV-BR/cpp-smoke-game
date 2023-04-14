#pragma once

#include <string>
#include <unordered_map>

#include "physics/vector.hpp"

struct Vertex {
  Vector3 position;
  Vector3 normal;
  Vector2 uv;

  Vertex(Vector3 position, Vector3 normal, Vector2 uv)
      : position(position), normal(normal), uv(uv) {}

  bool operator==(const Vertex& a) const {
    return a.position == position && a.normal == normal && a.uv == uv;
  };
};

template <>
struct std::hash<Vertex> {
  size_t operator()(const Vertex& v) const {
    return std::hash<Vector3>()(v.position);
  }
};