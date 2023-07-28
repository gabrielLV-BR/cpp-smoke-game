#include "./program.hpp"

#include <string>
#include <unordered_map>

#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"

Program::Program(Shader vertex, Shader fragment) : handle(glCreateProgram()) {
  glAttachShader(handle, vertex.handle);
  glAttachShader(handle, fragment.handle);
  glLinkProgram(handle);
}

Program::~Program() {
  glDeleteProgram(handle);
}

void Program::bind() {
  glUseProgram(handle);
}

void Program::unbind() {
  glUseProgram(0);
}

int Program::get_uniform_location(const std::string& name) const {
  return glGetUniformLocation(handle, name.c_str());
}

void Program::_internal_set_uniform(int location, int value) {
  glUniform1i(location, value);
}

void Program::_internal_set_uniform(int location, float value) {
  glUniform1f(location, value);
}

void Program::_internal_set_uniform(int location, const glm::mat4& mat) {
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::_internal_set_uniform(int location, const Texture& t) {
  glUniform1i(location, t.handle);
}