#pragma once

#include <spdlog/spdlog.h>
#include <memory>
#include <experimental/source_location>

template<typename T>
using Ref = std::shared_ptr<T>;

namespace Vision {
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

#define CORE_TRACE(...)    Vision::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...)    Vision::Logger::GetCoreLogger()->debug(__VA_ARGS__)
#define CORE_INFO(...)     Vision::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     Vision::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    Vision::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) Vision::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define APP_TRACE(...)    Vision::Logger::GetApplicationLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...)    Vision::Logger::GetApplicationLogger()->debug(__VA_ARGS__)
#define APP_INFO(...)     Vision::Logger::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_WARN(...)     Vision::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)    Vision::Logger::GetApplicationLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...) Vision::Logger::GetApplicationLogger()->critical(__VA_ARGS__)