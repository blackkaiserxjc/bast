#pragma once

#include <string_view>

namespace spdlog {
namespace level {
#define LOG_LEVEL_NAME_TRACE std::string_view("trace", 5)
#define LOG_LEVEL_NAME_DEBUG std::string_view("debug", 5)
#define LOG_LEVEL_NAME_INFO std::string_view("info", 4)
#define LOG_LEVEL_NAME_WARNING std::string_view("warn", 4)
#define LOG_LEVEL_NAME_ERROR std::string_view("error", 5)
#define LOG_LEVEL_NAME_CRIT std::string_view("crit", 4)
#define LOG_LEVEL_NAME_OFF std::string_view("off", 3)

#if !defined(SPDLOG_LEVEL_NAMES)
#define SPDLOG_LEVEL_NAMES          \
    {                               \
        LOG_LEVEL_NAME_TRACE,       \
            LOG_LEVEL_NAME_DEBUG,   \
            LOG_LEVEL_NAME_INFO,    \
            LOG_LEVEL_NAME_WARNING, \
            LOG_LEVEL_NAME_ERROR,   \
            LOG_LEVEL_NAME_CRIT,    \
            LOG_LEVEL_NAME_OFF      \
    }
#endif

} // namespace level
} // namespace spdlog