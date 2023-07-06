#pragma once

#include <cstdint>
#include <vector>

#include "renderer/program.hpp"

class ProgramServer {
 private:
  // TODO remove this if the vector proves to be inneficient
  //  std::unordered_map<bitset, uint32_t> program_map;
  static std::vector<Program> programs;
  static ProgramServer* _instance;

  ProgramServer() {}

 public:
  static void initialize() {
    if (_instance == nullptr) {
      _instance = new ProgramServer();
    }
  }

  static void destroy() { free(_instance); }

  static void store_program(Program program) {
    bool exists = false;

    for (const auto& p : programs)
      exists |= p == program;

    if (!exists)
      programs.push_back(program);
  }

  static void load_default_programs() {
    {  // BASIC
      Shader basic_frag_shader = Shader::load_from_file(
          ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);
      Shader basic_vert_shader = Shader::load_from_file(
          ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);

      Program basic_program = Program(basic_frag_shader, basic_vert_shader);
      store_program(basic_program);
    }
  }
};