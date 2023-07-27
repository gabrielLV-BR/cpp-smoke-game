#pragma once

#include <memory>
#include <cstdint>
#include <bitset>
#include <unordered_map>

#include "renderer/program.hpp"

class ProgramServer {
 public:
  static std::unordered_map<Program::bitset, std::shared_ptr<Program>> programs;
  static void initialize();

  static void store_program_for_bits(Program p, Program::bitset bits);
  static std::shared_ptr<Program> get_program_for(Material*);
};