#include "app.hpp"

#include "log/log.hpp"

#include <exception>

using log::Logger;

int main() {
  App app(500, 500, "OpenGL Box");

  try {
    app.Run();
  } catch(const std::exception& e) {
    Logger::error("Exception while running app: ", e.what());
    return -1;
  }

  return 0;
}