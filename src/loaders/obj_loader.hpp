#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "physics/vector.hpp"
#include "renderer/vertex.hpp"

struct ObjLoaderConfig {
  std::string folder;

  ObjLoaderConfig(std::string folder) : folder(folder) {}

 private:
  std::string ensure_trailing_backslash(std::string folder) {
    return folder + (folder[folder.length() - 1] == '/' ? '\0' : '/');
  }
};

class ObjLoader {
 public:
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
  std::vector<Vector3> vertex_positions;

 private:
  struct Face {
    uint32_t position_index, normal_index, uv_index;

    Face(uint32_t pos, uint32_t nor, uint32_t uv)
        : position_index(pos), normal_index(nor), uv_index(uv) {}
  };

  ObjLoaderConfig config;

  std::vector<Vector3> vertex_normals;
  std::vector<Vector2> vertex_uvs;
  std::vector<Face> faces;

  std::unordered_map<Vertex, uint32_t> index_map;

  // Methods
 public:
  ObjLoader(ObjLoaderConfig config);

  void load(const std::string name);
  Vector3 parse_vector3(const std::string& line, int start, int end);
  Vector2 parse_vector2(const std::string& line, int start, int end);

 private:
  void insert_vertex(const Vertex& v);
  void load_vertex(const std::string& line);
  void load_face(const std::string& face);
  void load_material(const std::string& material_name);
  void load_texture(const std::string& texture_name);
};