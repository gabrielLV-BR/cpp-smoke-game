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

    int stride = (3 + 3 + 2) * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unbind();
    vertex_buffer.unbind();
    index_buffer.unbind();
  }

  ~Mesh() {
    vertex_buffer.destroy();
    index_buffer.destroy();
    glDeleteVertexArrays(1, &vao);
  }

  uint32_t num_indices() const { return index_buffer.data.size(); }

  void bind() { glBindVertexArray(vao); }

  void unbind() { glBindVertexArray(0); }
};