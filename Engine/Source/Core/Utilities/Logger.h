#pragma once

#include <spdlog/spdlog.h>
#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;

class Logger {
public:
	static void Initialize();

	static Ref<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }

	template<typename... Args>
	static void info(Args &&...args) {
		::Logger::GetCoreLogger()->info(std::forward<Args>(args)...);
	}
private:
	static Ref<spdlog::logger> m_CoreLogger;
};

#define CORE_TRACE(...)    ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)     ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Logger::GetCoreLogger()->critical(__VA_ARGS__)