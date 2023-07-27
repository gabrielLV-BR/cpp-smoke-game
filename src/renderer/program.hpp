#pragma once

#include <string>
#include <bitset>

#include "./shader.hpp"
#include "./texture.hpp"

// forward declare
namespace glm {
struct mat4;
};  // namespace glm

namespace ProgramUniforms {
const static std::string COLOR = "uColor";
}

enum ProgramBits {
  DIFFUSE_MAP = 1 << 0,
  NORMAL_MAP = 1 << 1,
};

struct Program {
  using bitset = std::bitset<8>;

  uint32_t handle;

  Program(Shader vertex, Shader fragment);
  ~Program();

  int get_uniform_location(const std::string& name) const;

  template <typename T>
  void set_uniform(std::string name, T value) {
    int location = get_uniform_location(name);

    if (location == -1)
      return;

    _internal_set_uniform(location, value);
  }

  void bind();
  void unbind();

  bool operator==(const Program& other) const { return handle == other.handle; }

 private:
  template <typename T>
  void _internal_set_uniform(int location, T value) {
    std::cout << "type not implemented\n";
  }

  void _internal_set_uniform(int location, int value);
  void _internal_set_uniform(int location, float value);
  void _internal_set_uniform(int location, const glm::mat4& mat);
  void _internal_set_uniform(int location, const Texture& t);
};

template <>
struct std::hash<Program> {
  size_t operator()(const Program& p) const {
    return std::hash<uint32_t>()(p.handle);
  }
};