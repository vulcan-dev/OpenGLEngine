#pragma once

#include <spdlog/spdlog.h>
#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;

namespace VK {
	class Logger {
	public:
		static void Initialize();

		static Ref<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		static Ref<spdlog::logger>& GetApplicationLogger() { return m_ApplicationLogger; }
	private:
		static Ref<spdlog::logger> m_CoreLogger;
		static Ref<spdlog::logger> m_ApplicationLogger;
	};
}

#define CORE_TRACE(...)    VK::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...)    VK::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define CORE_INFO(...)     VK::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     VK::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    VK::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) VK::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define APP_TRACE(...)    VK::Logger::GetApplicationLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...)    VK::Logger::GetApplicationLogger()->debug(__VA_ARGS__)
#define APP_INFO(...)     VK::Logger::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_WARN(...)     VK::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)    VK::Logger::GetApplicationLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...) VK::Logger::GetApplicationLogger()->critical(__VA_ARGS__)