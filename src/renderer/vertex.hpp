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
};

struct VertexHash {
  size_t operator()(const Vertex& v) const {
    return std::hash<float>()(v.position.x) ^ std::hash<float>()(v.position.y) ^
           std::hash<float>()(v.position.z);
  };
};

struct VertexEqual {
  bool operator()(const Vertex& a, const Vertex& b) const {
    return a.position == b.position;
  };
};