#include "./program_server.hpp"

#include <memory>

#include "renderer/material.hpp"
#include "renderer/program.hpp"

void ProgramServer::initialize() {
  {  // COLORED
    Shader colored_frag_shader = Shader::load_from_file(
        ASSETS "shaders/colored.frag.glsl", ShaderType::FRAGMENT);
    Shader colored_vert_shader = Shader::load_from_file(
        ASSETS "shaders/colored.vert.glsl", ShaderType::VERTEX);

    store_program_for_bits(Program(colored_frag_shader, colored_vert_shader),
                           0);
  }

  {  // BASIC
    Shader basic_frag_shader = Shader::load_from_file(
        ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);
    Shader basic_vert_shader = Shader::load_from_file(
        ASSETS "shaders/basic.vert.glsl", ShaderType::VERTEX);

    store_program_for_bits(Program(basic_frag_shader, basic_vert_shader),
                           ProgramBits::DIFFUSE_MAP | ProgramBits::NORMAL_MAP);
  }
}

void ProgramServer::store_program_for_bits(Program p, Program::bitset bits) {
  programs[bits] = std::make_shared<Program>(p);
}

std::shared_ptr<Program> ProgramServer::get_program_for(Material* material) {
  Program::bitset bits = material->get_bits();
  return programs[bits];
}