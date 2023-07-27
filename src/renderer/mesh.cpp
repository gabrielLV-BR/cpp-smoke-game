#include "./mesh.hpp"

#include "glad/glad.h"

Mesh::Mesh(std::string name, std::vector<Vertex> vertices,
           std::vector<uint32_t> indices)
    : name(name),
      vertex_buffer(GL_ARRAY_BUFFER, vertices),
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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
    : Mesh("", vertices, indices) {}

Mesh::~Mesh() {
  vertex_buffer.destroy();
  index_buffer.destroy();
  glDeleteVertexArrays(1, &vao);
}

uint32_t Mesh::index_count() const { return index_buffer.data.size(); }
uint32_t Mesh::vertex_count() const { return vertex_buffer.data.size(); }

void Mesh::bind() { glBindVertexArray(vao); }

void Mesh::unbind() { glBindVertexArray(0); }