#pragma once

#include <cstdint>
#include <vector>

#include "renderer/program.hpp"

class ProgramServer {
  using bitset = Program::bitset;

 private:
  // TODO remove this if the vector proves to be inneficient
  //  std::unordered_map<bitset, uint32_t> program_map;
  static std::vector<Program> programs;

 public:
  ProgramServer();

  static void store_program(Program program);
  static Program find_program_with_bitset(bitset bits);

  static void load_default_programs();

  // Singleton stuff

  static void initialize();
  static void destroy();

 private:
  static ProgramServer* _instance;
};