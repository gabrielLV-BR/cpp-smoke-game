#pragma once

#include <cstdint>
#include <string>

#include "renderer/buffer.hpp"
#include "renderer/material.hpp"
#include "renderer/vertex.hpp"

struct Mesh {
  uint32_t vao;
  std::string name;

  StandardMaterial material;
  Buffer<Vertex> vertex_buffer;
  Buffer<uint32_t> index_buffer;

  Mesh(std::string, std::vector<Vertex>, std::vector<uint32_t>);
  Mesh(std::vector<Vertex>, std::vector<uint32_t>);
  ~Mesh();

  uint32_t index_count() const;
  uint32_t vertex_count() const;

  void bind();
  void unbind();
};