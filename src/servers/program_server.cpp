#include "./program_server.hpp"

ProgramServer::ProgramServer() {}

void ProgramServer::store_program(Program program) {
  bool exists = false;

  for (const auto& p : programs)
    exists |= p == program;

  if (!exists)
    programs.push_back(program);
}

Program get_program_by_material(StandardMaterial& material) {
  // TODO
  return;
}

void ProgramServer::load_default_programs() {
  {  // BASIC
    Shader basic_frag_shader = Shader::load_from_file(
        ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);
    Shader basic_vert_shader = Shader::load_from_file(
        ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);

    Program basic_program = Program(basic_frag_shader, basic_vert_shader);
    store_program(basic_program);
  }
}

ProgramServer& ProgramServer::get_global_instance() {
  static ProgramServer p;
  return p;
}