#pragma once

#include <vector>

#include "glad/glad.h"

template <typename T>
struct Buffer {
  std::vector<T> data;
  uint32_t handle;
  uint32_t target;

  Buffer() {}
  Buffer(uint32_t target, std::vector<T> data) : target(target), data(data) {
    glGenBuffers(1, &handle);
    glBindBuffer(target, handle);
    glBufferData(target, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
  }

  void bind() { glBindBuffer(target, handle); }

  void unbind() { glBindBuffer(target, 0); }

  void destroy() { glDeleteBuffers(1, &handle); }
};
