#include "material.hpp"

#include "glad/glad.h"

#include "utils/color.hpp"
#include "servers/server.hpp"

Material::Material() : Material(Color(0.0, 0.0, 0.0), {}) {}

Material::Material(Color color) : Material(color, {}) {}

Material::Material(Color color, std::vector<Texture> maps)
    : color(color),
      maps(maps),
      _program(ProgramServer::get_program_for(this)) {}

Program::bitset Material::get_bits() const {
    Program::bitset bits;

    // TODO allow adjustable behaviour, like graphics options
    for (int i = 0; i < maps.size(); i++)
        bits |= 1 << i;

    return bits;
}

void Material::bind() const {
    _program->bind();
    _program->set_uniform<Color>(ProgramUniforms::COLOR, color);
}

void Material::unbind() const {
    _program->unbind();
}