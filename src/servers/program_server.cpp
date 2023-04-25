#include "./program_server.hpp"

ProgramServer::ProgramServer() {}

ProgramServer::~ProgramServer() {}

void ProgramServer::store_program(ProgramServer::bitset bits,
                                  uint32_t program_handle) {
  if (program_map.count(bits) > 0)
    return;

  program_map[bits] = program_handle;
}

uint32_t ProgramServer::get_program(ProgramServer::bitset bits) const {
  return program_map.at(bits);
}
