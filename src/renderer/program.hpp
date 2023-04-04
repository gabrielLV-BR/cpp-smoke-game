#pragma once

#include "glad/glad.h"

#include "./shader.hpp"

struct Program {
  uint32_t handle;

  Program(Shader vertex, Shader fragment) : handle(glCreateProgram()) {
    glAttachShader(handle, vertex.handle);
    glAttachShader(handle, fragment.handle);
    glLinkProgram(handle);
  }

  ~Program() { glDeleteProgram(handle); }

  void bind() { glUseProgram(handle); }

  void unbind() { glUseProgram(0); }
};