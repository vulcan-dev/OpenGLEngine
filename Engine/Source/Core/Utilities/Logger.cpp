#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

Ref<spdlog::logger> Logger::m_CoreLogger;

void Logger::Initialize() {
	std::vector<spdlog::sink_ptr> logSinks;
	logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

	m_CoreLogger = std::make_shared<spdlog::logger>("Engine", begin(logSinks), end(logSinks));
	spdlog::register_logger(m_CoreLogger);
	m_CoreLogger->set_level(spdlog::level::trace);
	m_CoreLogger->flush_on(spdlog::level::trace);
}