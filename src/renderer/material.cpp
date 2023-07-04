#include "./material.hpp"

#include "servers/program_server.hpp"

BaseMaterial::BaseMaterial()
    : BaseMaterial(ProgramServer::find_program_with_bitset(0).handle) {}

BaseMaterial::BaseMaterial(uint32_t program) {}

void BaseMaterial::bind() {
  // TODO bind
}

void BaseMaterial::unbind() {
  // TODO unbind
}