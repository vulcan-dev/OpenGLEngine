#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Vision {
    Ref<spdlog::logger> Logger::m_CoreLogger;
    Ref<spdlog::logger> Logger::m_ApplicationLogger;


    void Logger::Initialize() {
        std::vector<spdlog::sink_ptr> coreLogSinks;
        coreLogSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

        m_CoreLogger = std::make_shared<spdlog::logger>("Engine", begin(coreLogSinks), end(coreLogSinks));
        spdlog::register_logger(m_CoreLogger);
        m_CoreLogger->set_level(spdlog::level::trace);
        m_CoreLogger->flush_on(spdlog::level::trace);

        // Application Logger
        std::vector<spdlog::sink_ptr> appLogSinks;
        appLogSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

        m_ApplicationLogger = std::make_shared<spdlog::logger>("Application", begin(appLogSinks), end(appLogSinks));
        spdlog::register_logger(m_ApplicationLogger);
        m_ApplicationLogger->set_level(spdlog::level::trace);
        m_ApplicationLogger->flush_on(spdlog::level::trace);

#ifdef DEBUG_MODE
        m_CoreLogger->set_level(spdlog::level::debug);
        m_ApplicationLogger->set_level(spdlog::level::debug);

        m_CoreLogger->info("Running With Debug Mode");
#else
        m_CoreLogger->info("Running With Release Mode");
#endif
        }
}