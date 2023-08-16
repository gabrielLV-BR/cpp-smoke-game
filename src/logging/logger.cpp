#include "logger.hpp"

#ifndef NDEBUG

// debug

#include <iostream>

template <typename... T>
inline void Logger::log(T... data) {
    _recursiveOut(std::cout, data...);
}

template <typename... T>
inline void Logger::error(T... data) {
    _recursiveOut(std::cerr, data...);
}

template <typename T, typename... Args>
inline void
Logger::_recursiveOut(std::ostringstream& oss, T& arg, Args... args) {
    oss << arg;
    _recursiveOut(oss, args...);
}

inline void Logger::_recursiveOut(std::ostringstream& oss) {}

#else

// release

template <typename... T>
inline void Logger::log(T... data) {}

template <typename... T>
inline void Logger::error(T... data) {}

template <typename T, typename... Args>
inline void
Logger::_recursiveOut(std::ostringstream& oss, T& arg, Args... args) {}

inline void Logger::_recursiveOut(std::ostringstream& oss) {}

#endif
