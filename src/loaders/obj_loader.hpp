#pragma once

#include <stdio.h>
#include <cstdint>
#include <fstream>
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

  std::vector<Vector3> vertex_normals;
  std::vector<Vector2> vertex_uvs;
  std::vector<Face> faces;

 public:
  // TODO implement texture loading
  //  std::vector<Texture> textures;

  ObjLoaderConfig config;

  ObjLoader(ObjLoaderConfig config) : config(config) {}

  void load(const std::string name) {
    std::string model_path = config.folder + name;
    std::string line;
    line.reserve(50);

    FILE* file = fopen(model_path.c_str(), "r");

    char c_line[50];
    while (fgets(c_line, 50, file)) {
      line = c_line;

      switch (line[0]) {
        case '#':
          continue;  // comment
        case 'o':
          continue;  // object
        case 'm': {
          // make sure it says mtllib
          if (line.rfind("mttlib", 0) == 0) {
            // get material name
            const std::string material_name = line.substr(line.find(" "));
            load_material(material_name);
          }
          break;
        };
        case 'v':
          load_vertex(line);  // vertex {position, normal, uv}
          break;
        case 'f':
          load_face(line);  // face
          break;
      }
    }

    fclose(file);

    // load vertices and indices

    for (const auto& face : faces) {
      Vertex v(vertex_positions[face.position_index],
               vertex_normals[face.normal_index], vertex_uvs[face.uv_index]);

      // vertices.push_back(v);
      // indices.push_back(face.position_index);
      insert_vertex(v);
    }

    // clear all redundant data
    faces.clear();
    vertex_normals.clear();
    // vertex_positions.clear();
    vertex_uvs.clear();
  }

  Vector3 parse_vector3(const std::string& line, int start, int end) {
    int first_space = line.find(" ", start);
    int last_space = line.rfind(" ", end);

    std::string a = line.substr(start, first_space - start);
    std::string b = line.substr(first_space + 1, last_space - first_space - 1);
    std::string c = line.substr(last_space + 1, end - last_space - 1);

    const float x = std::stof(a);
    const float y = std::stof(b);
    const float z = std::stof(c);

    return Vector3(x, y, z);
  }

  Vector2 parse_vector2(const std::string& line, int start, int end) {
    const int first_space = line.find(" ", start);

    const std::string a = line.substr(start, first_space - start);
    const std::string b = line.substr(first_space + 1, end - first_space - 1);

    const float x = std::stof(a);
    const float y = std::stof(b);

    return Vector2{x, y};
  }

 private:
  void load_vertex(const std::string& line) {
    switch (line[1]) {
      case ' ':
        // vertex position
        vertex_positions.push_back(parse_vector3(line, 2, line.length()));
        break;
      case 'n':
        // vertex normal
        vertex_normals.push_back(parse_vector3(line, 3, line.length()));
        break;
      case 't':
        // vertex uv
        vertex_uvs.push_back(parse_vector2(line, 3, line.length()));
        break;
    }
  }

  void insert_vertex(const Vertex& v) {
    static std::unordered_map<Vertex, uint32_t, VertexHash, VertexEqual>
        index_map;

    if (index_map.count(v) > 0) {
      // duplicate vertex
      indices.push_back(index_map.at(v));
    } else {
      // new vertex
      vertices.push_back(v);
      uint32_t vertex_index = vertices.size() - 1;
      index_map[v] = vertex_index;
      indices.push_back(vertex_index);
    }
  }

  void load_face(const std::string& face) {
    using std::string;

    int vertex_index = 0;
    int normal_index = 0;
    int uv_index = 0;

    int first_space = 0;
    int second_space = 0;

    for (int i = 0; i < 3; i++) {
      first_space = face.find(" ", first_space + 1);
      second_space = face.find_first_of(" \n", first_space + 1);

      int first_separator = face.find("/", first_space);
      int second_separator = face.rfind("/", second_space);

      string vertex_index_string =
          face.substr(first_space + 1, first_separator - first_space - 1);
      string normal_index_string = face.substr(
          first_separator + 1, second_separator - first_separator - 1);
      string uvcoord_index_string = face.substr(
          second_separator + 1, second_space - second_separator - 1);

      uint32_t vertex_index = std::stoi(vertex_index_string);
      uint32_t normal_index = std::stoi(normal_index_string);
      uint32_t uv_index = std::stoi(uvcoord_index_string);

      // indices.emplace_back(vertex_index);
      faces.emplace_back(vertex_index, normal_index, uv_index);
    }
  }

  void load_material(const std::string& material_name) {
    std::string material_path = config.folder + material_name;
    std::string line, texture_name;

    std::ifstream file(material_path);

    while (std::getline(file, line)) {
      if (line[0] == 'm' && line.rfind("map_Kd", 0) == 0) {
        // found line that specifies diffuse texture
        texture_name = line.substr(line.find(" "));
        load_texture(texture_name);
      }
    }
  }

  void load_texture(const std::string& texture_name) {
    // TODO handle it
  }

  //
};