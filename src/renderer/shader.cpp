#include "./shader.hpp"
#include "utils/file.hpp"

Shader::Shader(std::string source, ShaderType shader_type)
    : shader_type(shader_type) {
  handle = glCreateShader(static_cast<uint32_t>(shader_type));

  glShaderSource(handle, 1, reinterpret_cast<const char**>(&source), NULL);
  glCompileShader(handle);

  check_for_errors();
}

Shader::~Shader() {
  glDeleteShader(handle);
}

Shader Shader::load_from_file(std::string path, ShaderType shader_type) {
  std::string source = utils::read_file_contents(path);
  return Shader(source, shader_type);
}

void Shader::check_for_errors() {
  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(handle, 512, nullptr, info_log);
    // TODO put this into separate LOG class
    std::cout << "[ERROR COMPILING "
              << (shader_type == ShaderType::FRAGMENT ? "FRAGMENT" : "VERTEX")
              << " SHADER!]\t" << info_log << '\n';
  }
}