#pragma once

#include <string>

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

  int get_uniform_location(const std::string& name) const {
    return glGetUniformLocation(handle, name.c_str());
  }

  template <typename T>
  void set_uniform(std::string name, T value) {
    int location = get_uniform_location(name);

    if (location == -1)
      return;

    _internal_set_uniform(location, value);
  }

  void bind() { glUseProgram(handle); }

  void unbind() { glUseProgram(0); }

 private:
  template <typename T>
  void _internal_set_uniform(int location, T value) {
    std::cout << "type not implemented\n";
  }

  void _internal_set_uniform(int location, int value) {
    glUniform1i(location, value);
  }

  void _internal_set_uniform(int location, float value) {
    glUniform1f(location, value);
  }
};