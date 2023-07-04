#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "physics/vector.hpp"
#include "renderer/model.hpp"
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

 private:
  ObjLoaderConfig config;

  std::string object_name;
  std::vector<Vector3> vertex_positions;
  std::vector<Vector3> vertex_normals;
  std::vector<Vector2> vertex_uvs;
  std::vector<BaseMaterial*> materials;

  std::unordered_map<Vertex, uint32_t> index_map;

  // Methods
 public:
  ObjLoader(ObjLoaderConfig config);

  Model load(const std::string name);
  Vector3 parse_vector3(const std::string& line, int start, int end);
  Vector2 parse_vector2(const std::string& line, int start, int end);

 private:
  void read_file(const std::string& file_path);
  void read_material(const std::string& material_path);

  void insert_vertex(const Vertex& v);
  void load_vertex(const std::string& line);
  void load_face(const std::string& face);
};