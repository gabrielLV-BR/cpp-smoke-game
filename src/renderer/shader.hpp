#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "glad/glad.h"

enum ShaderType { VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER };

struct Shader {
  uint32_t handle;
  ShaderType shader_type;

  int success;

  Shader(std::string source, ShaderType shader_type);
  ~Shader();

  static Shader load_from_file(std::string path, ShaderType shader_type);

  void check_for_errors();
};