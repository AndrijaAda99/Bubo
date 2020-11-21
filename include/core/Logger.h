#ifndef BUBO_LOGGER_H
#define BUBO_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace bubo {

    class Logger {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger>& getCoreLogger() {
            return s_coreLogger;
        }
        static std::shared_ptr<spdlog::logger>& getDebugLogger() {
            return s_debugLogger;
        }
    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_debugLogger;
    };

}

#define BUBO_TRACE(...)    ::bubo::Logger::getCoreLogger()->trace(__VA_ARGS__)
#define BUBO_INFO(...)     ::bubo::Logger::getCoreLogger()->info(__VA_ARGS__)
#define BUBO_WARN(...)     ::bubo::Logger::getCoreLogger()->warn(__VA_ARGS__)
#define BUBO_ERROR(...)    ::bubo::Logger::getCoreLogger()->error(__VA_ARGS__)
#define BUBO_CRITICAL(...) ::bubo::Logger::getCoreLogger()->critical(__VA_ARGS__)

#ifdef DEBUG_MODE

#define BUBO_DEBUG_TRACE(...)    ::bubo::Logger::getDebugLogger()->trace(__VA_ARGS__)
#define BUBO_DEBUG_INFO(...)     ::bubo::Logger::getDebugLogger()->info(__VA_ARGS__)
#define BUBO_DEBUG_WARN(...)     ::bubo::Logger::getDebugLogger()->warn(__VA_ARGS__)
#define BUBO_DEBUG_ERROR(...)    ::bubo::Logger::getDebugLogger()->error(__VA_ARGS__)
#define BUBO_DEBUG_CRITICAL(...) ::bubo::Logger::getDebugLogger()->critical(__VA_ARGS__)

#else

#define BUBO_DEBUG_INFO(...)
#define BUBO_DEBUG_TRACE(...)
#define BUBO_DEBUG_WARN(...)
#define BUBO_DEBUG_ERROR(...)
#define BUBO_DEBUG_CRITICAL(...)

#endif //DEBUG_MODE

#endif //BUBO_LOGGER_H

