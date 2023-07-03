#pragma once

#include <cstdint>
#include <vector>

#include "renderer/program.hpp"

class ProgramServer {
  using bitset = Program::bitset;

 private:
  // TODO remove this if the vector proves to be inneficient
  //  std::unordered_map<bitset, uint32_t> program_map;
  std::vector<Program> programs;

 public:
  ProgramServer();
  ~ProgramServer();

  void store_program(Program program);
  Program find_program_with_bitset(bitset bits) const;

  // Singleton stuff

 public:
  static ProgramServer* get_global_instance() {
    if (_instance == nullptr) {
      *_instance = ProgramServer();
    }
    return _instance;
  }

 private:
  static ProgramServer* _instance;
};