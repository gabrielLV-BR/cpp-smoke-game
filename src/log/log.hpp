#pragma once

namespace log {
    class Logger {
    public:
        template <typename... T>
        inline static void log(T... data);
    };
}