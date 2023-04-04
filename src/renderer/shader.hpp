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

  Shader(std::string source, ShaderType shader_type)
      : shader_type(shader_type) {
    handle = glCreateShader(static_cast<uint32_t>(shader_type));

    glShaderSource(handle, 1, reinterpret_cast<const char**>(&source), NULL);
    glCompileShader(handle);

    check_for_errors();
  }

  ~Shader() { glDeleteShader(handle); }

  void check_for_errors() {
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

    if (!success) {
      char info_log[512];
      glGetShaderInfoLog(handle, 512, nullptr, info_log);
      std::cout << "[ERROR COMPILING "
                << (shader_type == ShaderType::FRAGMENT ? "FRAGMENT" : "VERTEX")
                << " SHADER!]\t" << info_log << '\n';
    }
  }
};