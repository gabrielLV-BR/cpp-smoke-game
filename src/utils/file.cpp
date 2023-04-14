#include "./file.hpp"

std::string utils::read_file_contents(const std::string& path) {
  std::ifstream file(path);
  std::stringstream sstream;

  sstream << file.rdbuf();

  return sstream.str();
}