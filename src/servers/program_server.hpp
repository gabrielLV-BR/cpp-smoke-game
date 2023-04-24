#pragma once

#include <cstdint>
#include <unordered_set>

#include "renderer/program.hpp"

class ProgramServer {
  using bitset = uint8_t;

  std::unordered_set<bitset, uint32_t> program_set;

  static ProgramServer* _instance;

 public:
  ProgramServer();
  ~ProgramServer();

  void store_program(bitset bits, uint32_t program_handle);
  uint32_t get_program(bitset bits);

  static ProgramServer* get_global_instance();
};