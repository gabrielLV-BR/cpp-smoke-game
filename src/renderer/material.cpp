#include "material.hpp"

#include "glad/glad.h"

#include "utils/color.hpp"
#include "servers/server.hpp"

Material::Material() : Material(Color(0.0, 0.0, 0.0), {}) {}

Material::Material(Color color) : Material(color, {}) {}

Material::Material(Color color, std::vector<Texture> maps)
    : color(color), maps(maps) {}

Program::bitset Material::GetBits() const {
    Program::bitset bits;

    // TODO allow adjustable behaviour, like graphics options
    for (int i = 0; i < maps.size(); i++)
        bits |= 1 << i;

    return bits;
}

void Material::Bind() const {
    _program->Bind();
    _program->SetUniform<Color>(ProgramUniforms::COLOR, color);
}

void Material::Unbind() const {
    _program->Unbind();
}