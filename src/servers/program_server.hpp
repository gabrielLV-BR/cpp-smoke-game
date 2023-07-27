#pragma once

#include <memory>
#include <cstdint>
#include <vector>

#include "renderer/program.hpp"

class ProgramServer {
 private:
  // TODO remove this if the vector proves to be inneficient
  //  std::unordered_map<bitset, uint32_t> program_map;
  std::vector<Program> programs;

 public:
  void store_program(Program program);
  Program get_program_by_material(StandardMaterial& material);
  void load_default_programs();

  // Singleton stuff
  static ProgramServer& get_global_instance();

 private:
  ProgramServer();
};