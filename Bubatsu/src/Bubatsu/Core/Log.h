#pragma once

#include "Bubatsu/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Bubatsu
{
    class BUBATSU_API Log
    {
    public:
        static void Init();

        inline static SPtr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
        inline static SPtr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

    private:
        static SPtr<spdlog::logger> m_CoreLogger;
        static SPtr<spdlog::logger> m_ClientLogger;
    };
}

// Core Logging Macros
#define BBZ_CORE_FATAL(...) ::Bubatsu::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define BBZ_CORE_ERROR(...) ::Bubatsu::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BBZ_CORE_WARN(...)  ::Bubatsu::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BBZ_CORE_INFO(...)  ::Bubatsu::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BBZ_CORE_TRACE(...) ::Bubatsu::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client Logging Macros
#define BBZ_FATAL(...)      ::Bubatsu::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define BBZ_ERROR(...)      ::Bubatsu::Log::GetClientLogger()->error(__VA_ARGS__)
#define BBZ_WARN(...)       ::Bubatsu::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BBZ_INFO(...)       ::Bubatsu::Log::GetClientLogger()->info(__VA_ARGS__)
#define BBZ_TRACE(...)      ::Bubatsu::Log::GetClientLogger()->trace(__VA_ARGS__)