#include "./buffer.hpp"

#include "glad/glad.h"

template class Buffer<Vertex>;
template class Buffer<uint32_t>;

template <typename T>
Buffer<T>::Buffer(uint32_t target, std::vector<T> data)
    : target(target), data(data) {
  glGenBuffers(1, &handle);
  glBindBuffer(target, handle);
  glBufferData(target, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}

template <typename T>
Buffer<T>::~Buffer() {
  glDeleteBuffers(1, &handle);
}

template <typename T>
void Buffer<T>::bind() {
  glBindBuffer(target, handle);
}

template <typename T>
void Buffer<T>::unbind() {
  glBindBuffer(target, 0);
}
