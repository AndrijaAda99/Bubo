#include "core/Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace bubo {

    std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_debugLogger;

    void Logger::init() {

		std::vector<spdlog::sink_ptr> coreSinks;
        std::vector<spdlog::sink_ptr> debugSinks;

        coreSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        coreSinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("bubo.log"));

        debugSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        debugSinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("bubo_debug.log"));

        coreSinks[0]->set_pattern("[%T] [%n: %^%l%$] %v");
        coreSinks[1]->set_pattern("[%T] [%n: %l] %v");

        // TODO: find some better way for debug pattern
        debugSinks[0]->set_pattern("[%T] [%^%n: %l%$] %v");
        debugSinks[1]->set_pattern("[%T] [%n: %l] %v");

        s_coreLogger = std::make_shared<spdlog::logger>("BUBO", coreSinks.begin(), coreSinks.end());
        s_debugLogger = std::make_shared<spdlog::logger>("BUBO_DEBUG", debugSinks.begin(), debugSinks.end());

        spdlog::register_logger(s_coreLogger);
        spdlog::register_logger(s_debugLogger);

        s_coreLogger->set_level(spdlog::level::trace);
        s_coreLogger->flush_on(spdlog::level::trace);

        s_debugLogger->set_level(spdlog::level::trace);
        s_debugLogger->flush_on(spdlog::level::trace);
    }

}
