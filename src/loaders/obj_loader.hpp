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
  std::unordered_map<Vertex, uint32_t> index_map;

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

    // for (const auto& face : faces) {
    //   Vertex v(vertex_positions[face.position_index],
    //            vertex_normals[face.normal_index], vertex_uvs[face.uv_index]);

    //   vertices.push_back(v);
    //   indices.push_back(face.position_index);
    //   insert_vertex(v);
    // }

    // clear all redundant data
    faces.clear();
    vertex_normals.clear();
    vertex_positions.clear();
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

    uint vertex_indices[3];
    uint normal_indices[3];
    uint uv_indices[3];

    int matches =
        sscanf(face.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
               &vertex_indices[0], &normal_indices[0], &uv_indices[0],
               &vertex_indices[1], &normal_indices[1], &uv_indices[1],
               &vertex_indices[2], &normal_indices[2], &uv_indices[2]);

    if (matches != 9) {
#ifndef NDEBUG
      std::cout << "Couldn't read face. Aborting.\n";
#endif
      return;
    }

    for (int i = 0; i < 3; i++) {
      Vector3 vertex_position = vertex_positions[vertex_indices[i] - 1];
      Vector3 vertex_normal = vertex_normals[normal_indices[i] - 1];
      Vector2 vertex_uv = vertex_uvs[uv_indices[i] - 1];

      Vertex v(vertex_position, vertex_normal, vertex_uv);
      insert_vertex(v);
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