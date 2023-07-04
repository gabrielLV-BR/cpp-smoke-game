#include "./program_server.hpp"

ProgramServer::ProgramServer() {}

void ProgramServer::initialize() {
  if (_instance == nullptr) {
    _instance = new ProgramServer();
  }
}

void ProgramServer::destroy() {
  free(_instance);
}

void ProgramServer::store_program(Program program) {
  bool exists = false;

  for (const auto& p : programs)
    exists |= p == program;

  if (!exists)
    programs.push_back(program);
}

Program ProgramServer::find_program_with_bitset(ProgramServer::bitset bits) {
  for (const auto& p : programs) {
    if ((p.features_bitset & bits) != 0)
      return p;
  }
}
