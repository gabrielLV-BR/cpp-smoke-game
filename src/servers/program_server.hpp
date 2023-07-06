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

 public:
  ProgramServer();

  static void store_program(Program program);
  static void load_default_programs();

  // Singleton stuff

  static void initialize();
  static void destroy();
};