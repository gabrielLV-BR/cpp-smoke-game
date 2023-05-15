#pragma once

#include <cstdint>
#include <unordered_map>

#include "renderer/program.hpp"

class ProgramServer {
 public:
  using bitset = uint8_t;

 private:
  std::unordered_map<bitset, uint32_t> program_map;
  static ProgramServer* _instance;

 public:
  ProgramServer();
  ~ProgramServer();

  void store_program(bitset bits, uint32_t program_handle);
  uint32_t get_program(bitset bits) const;

  static ProgramServer* get_global_instance() {
    if (_instance == nullptr) {
      *_instance = ProgramServer();
    }
    return _instance;
  }
};