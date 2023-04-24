#include "./program_server.hpp"

ProgramServer::ProgramServer() {}

ProgramServer::~ProgramServer() {}

ProgramServer* ProgramServer::get_global_instance() {
  if (_instance == nullptr) {
    *_instance = ProgramServer();
  }
  return _instance;
}