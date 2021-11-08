#pragma once

#include <spdlog/spdlog.h>
#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;

class Logger {
public:
	static void Initialize();

	static Ref<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
	static Ref<spdlog::logger>& GetApplicationLogger() { return m_ApplicationLogger; }
private:
	static Ref<spdlog::logger> m_CoreLogger;
	static Ref<spdlog::logger> m_ApplicationLogger;
};

#define CORE_TRACE(...)    ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...)    ::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define CORE_INFO(...)     ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define APP_TRACE(...)    ::Logger::GetApplicationLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...)    ::Logger::GetApplicationLogger()->debug(__VA_ARGS__)
#define APP_INFO(...)     ::Logger::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_WARN(...)     ::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)    ::Logger::GetApplicationLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...) ::Logger::GetApplicationLogger()->critical(__VA_ARGS__)