#include "app.hpp"

#include <exception>

#include "logging/logger.hpp"

int main() {
    App app(500, 500, "OpenGL Box");

    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        return -1;
    }

    return 0;
}