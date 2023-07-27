#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "renderer/program.hpp"
#include "renderer/texture.hpp"
#include "utils/color.hpp"

struct Material {
  // this must be set up by program_server
  std::shared_ptr<Program> _program;

  Color color;
  std::vector<Texture> maps;

  Material();
  Material(Color color);
  Material(Color color, std::vector<Texture> maps);

  Program::bitset get_bits() const;

  void bind() const;
  void unbind() const;
};