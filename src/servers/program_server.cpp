// #include "./program_server.hpp"

// ProgramServer::ProgramServer() {}

// void ProgramServer::initialize() {
//   if (ProgramServer::_instance == nullptr) {
//     ProgramServer::_instance = new ProgramServer();
//   }
// }

// void ProgramServer::destroy() {
//   free(ProgramServer::_instance);
// }

// void ProgramServer::store_program(Program program) {
//   bool exists = false;

//   for (const auto& p : programs)
//     exists |= p == program;

//   if (!exists)
//     programs.push_back(program);
// }

// void ProgramServer::load_default_programs() {
//   {  // BASIC
//     Shader basic_frag_shader = Shader::load_from_file(
//         ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);
//     Shader basic_vert_shader = Shader::load_from_file(
//         ASSETS "shaders/basic.frag.glsl", ShaderType::FRAGMENT);

//     Program basic_program = Program(basic_frag_shader, basic_vert_shader);
//     store_program(basic_program);
//   }
// }