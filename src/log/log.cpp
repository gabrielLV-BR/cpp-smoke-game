#include "log.hpp"

using namespace log;

#ifndef NDEBUG

// debug

#include <iostream>

template<typename... T>
inline void Logger::log(T... data) {
    std::cout << ...data << std::endl;
}

#else

// release

template<typename... T>
inline void Logger::log(T... data) {}

#endif
