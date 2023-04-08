#pragma once

#include <cstdint>

#include "glad/glad.h"
#include "renderer/buffer.hpp"
#include "renderer/vertex.hpp"

struct Mesh {
  uint32_t vao;
  Buffer<Vertex> vertex_buffer;
  Buffer<uint32_t> index_buffer;

  Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
      : vertex_buffer(GL_ARRAY_BUFFER, vertices),
        index_buffer(GL_ELEMENT_ARRAY_BUFFER, indices) {
    glGenVertexArrays(1, &vao);

    bind();
    vertex_buffer.bind();
    index_buffer.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    unbind();
    vertex_buffer.unbind();
    index_buffer.unbind();
  }

  ~Mesh() {
    vertex_buffer.destroy();
    index_buffer.destroy();
    glDeleteVertexArrays(1, &vao);
  }

  void bind() { glBindVertexArray(vao); }

  void unbind() { glBindVertexArray(0); }
};