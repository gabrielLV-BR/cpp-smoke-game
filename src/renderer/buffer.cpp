#include "./buffer.hpp"

#include "glad/glad.h"
#include <vector>

template struct Buffer<Vertex>;
template struct Buffer<uint32_t>;

template <typename T>
Buffer<T>::Buffer() {}

template <typename T>
Buffer<T>::Buffer(uint32_t target, std::vector<T> data)
    : target(target), data(data) {
  glGenBuffers(1, &handle);
  glBindBuffer(target, handle);
  glBufferData(target, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}

template <typename T>
void Buffer<T>::bind() {
  glBindBuffer(target, handle);
}

template <typename T>
void Buffer<T>::unbind() {
  glBindBuffer(target, 0);
}

template <typename T>
void Buffer<T>::destroy() {
  glDeleteBuffers(1, &handle);
}
