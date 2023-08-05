#include "logger.hpp"

#ifndef NDEBUG

// debug

#include <iostream>

template <typename... T>
inline void Logger::log(T... data) {
    std::cout << ... data << std::endl;
}

template <typename... T>
inline void Logger::error(T... data) {
    std::cerr << ... data << std::endl;
}

#else

// release

template <typename... T>
inline void Logger::log(T... data) {}

template <typename... T>
inline void Logger::error(T... data) {}

#endif