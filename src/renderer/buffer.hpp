#pragma once

#include <vector>
#include <cstdint>

#include "renderer/vertex.hpp"

template <typename T>
struct Buffer {
  std::vector<T> data;
  uint32_t handle;
  uint32_t target;

  Buffer();
  Buffer(uint32_t target, std::vector<T> data);

  void bind();
  void unbind();
  void destroy();
};

extern template struct Buffer<uint32_t>;
extern template struct Buffer<Vertex>;