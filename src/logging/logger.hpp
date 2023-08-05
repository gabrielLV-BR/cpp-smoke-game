#pragma once

class Logger {
   public:
    template <typename... T>
    inline static void log(T... data);

    template <typename... T>
    inline static void error(T... data);
};