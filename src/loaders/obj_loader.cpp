#include <stdio.h>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "./obj_loader.hpp"
ObjLoader::ObjLoader(ObjLoaderConfig config) : config(config) {}

Model ObjLoader::load(const std::string name) {
  std::string model_path = config.folder + name;

  read_file(model_path);
  // clear all redundant data
  vertex_normals.clear();
  vertex_positions.clear();
  vertex_uvs.clear();

  return {};
}

void ObjLoader::read_file(const std::string& file_path) {
  std::string line;
  line.reserve(50);

  FILE* file = fopen(file_path.c_str(), "r");

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
          const std::string material_name =
              config.folder + line.substr(line.find(" "));
          read_material(material_name);
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
}

void ObjLoader::read_material(const std::string& material_path) {
  std::string line, texture_name;

  std::ifstream file(material_path);

  std::vector<Texture> maps;

  while (std::getline(file, line)) {
    if (line[0] == 'm' && line.rfind("map_", 0) == 0) {
      // found line that specifies texture
      texture_name = line.substr(line.find(" "));

      Texture texture = Texture::from_file(texture_name);

      maps.push_back(texture);
    }
  }

  materials.push_back(StandardMaterial(Color{1.0, 1.0, 1.0}, maps));
}

Vector3 ObjLoader::parse_vector3(const std::string& line, int start, int end) {
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

Vector2 ObjLoader::parse_vector2(const std::string& line, int start, int end) {
  const int first_space = line.find(" ", start);

  const std::string a = line.substr(start, first_space - start);
  const std::string b = line.substr(first_space + 1, end - first_space - 1);

  const float x = std::stof(a);
  const float y = std::stof(b);

  return Vector2{x, y};
}

void ObjLoader::load_vertex(const std::string& line) {
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

void ObjLoader::insert_vertex(const Vertex& v) {
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

void ObjLoader::load_face(const std::string& face) {
  using std::string;

  uint vertex_indices[3];
  uint normal_indices[3];
  uint uv_indices[3];

  int matches = sscanf(face.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
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