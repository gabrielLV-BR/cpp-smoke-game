#include "./program_server.hpp"

ProgramServer::ProgramServer() {}

ProgramServer::~ProgramServer() {}

void ProgramServer::store_program(Program program) {
  bool exists = false;

  for (const auto& p : programs)
    exists |= p == program;

  if (!exists)
    programs.push_back(program);
}

Program ProgramServer::find_program_with_bitset(
    ProgramServer::bitset bits) const {
  for (const auto& p : programs) {
    if ((p.features_bitset & bits) != 0)
      return p;
  }
}
