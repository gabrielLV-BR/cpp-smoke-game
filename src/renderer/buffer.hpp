#pragma once

#include <vector>
#include <cstdint>

#include "vertex.hpp"

template <typename T>
class Buffer {
 public:
  std::vector<T> data;
  uint32_t handle;
  uint32_t target;

  Buffer(uint32_t target, std::vector<T> data);
  ~Buffer();

  void bind();
  void unbind();

 private:
  void initialize_innard() {}
};

// to shut up linker
extern template class Buffer<Vertex>;
extern template class Buffer<uint32_t>;