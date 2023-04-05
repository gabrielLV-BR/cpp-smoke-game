#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "physics/vector.hpp"
#include "renderer/vertex.hpp"

struct ObjLoaderConfig {
  std::string folder;

  ObjLoaderConfig(std::string folder)
      : folder(ensure_trailing_backslash(folder)) {}

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
  std::vector<Vector3> vertex_positions;
  std::vector<Vector3> vertex_normals;
  std::vector<Vector2> vertex_uvs;

 public:
  // TODO implement texture loading
  //  std::vector<Texture> textures;

  ObjLoaderConfig config;

  ObjLoader(ObjLoaderConfig config) : config(config) {}

  void load(std::string name) {
    std::string model_path = config.folder + name;
    std::string line;

    std::ifstream file(model_path);
    while (std::getline(file, line)) {
      switch (line[0]) {
        case '#':
          continue;  // comment
        case 'o':
          continue;  // object
        case 'm': {
          // make sure it says mtllib
          if (line.rfind("mttlib", 0) == 0) {
            // get material name
            std::string material_name = line.substr(line.find(" "));
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

    // TODO interlace separate vertex data into single vertex struct
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

  void load_face(const std::string& line) {}

  void load_material(const std::string& material_name) {
    std::string material_path = config.folder + material_name;
    std::string line;

    std::ifstream file(material_path);

    while (std::getline(file, line)) {
      if (line[0] == 'm' && line.rfind("map_Kd", 0) == 0) {
        // found line that specifies diffuse texture
        std::string texture_name = line.substr(line.find(" "));
        load_texture(texture_name);
      }
    }
  }

  void load_texture(const std::string& texture_name) {
    // TODO handle it
  }

  //

  Vector3 parse_vector3(const std::string& line, int start, int end) {
    int first_space = line.find(" ");
    int last_space = line.rfind(" ");

    std::string a = line.substr(start, first_space);
    std::string b = line.substr(first_space + 1, last_space);
    std::string c = line.substr(last_space + 1, end);

    float x = std::stof(a);
    float y = std::stof(b);
    float z = std::stof(c);

    return Vector3{x, y, z};
  }

  Vector2 parse_vector2(const std::string& line, int start, int end) {
    int first_space = line.find(" ");

    std::string a = line.substr(start, first_space);
    std::string b = line.substr(first_space + 1, end);

    float x = std::stof(a);
    float y = std::stof(b);

    return Vector2{x, y};
  }
};