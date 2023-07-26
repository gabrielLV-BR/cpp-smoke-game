#pragma once

#include <vector>
#include <cstdint>

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
