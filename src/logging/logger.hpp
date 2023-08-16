#pragma once

#include <iostream>
#include <ostream>
#include <sstream>

class Logger {
   public:
    template <typename... T>
    inline static void log(T... data);

    template <typename... T>
    inline static void error(T... data);

   private:
    template <typename T, typename... Args>
    inline static void
    _recursiveOut(std::ostringstream& oss, T& arg, Args... args);

    inline static void _recursiveOut(std::ostringstream& oss);
};