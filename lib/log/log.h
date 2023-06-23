#pragma once

#include <spdlog/spdlog.h>

namespace bast {
namespace log {

template <typename... Args>
using format_string_t = fmt::format_string<Args...>;

template <typename... Args>
inline void trace(format_string_t<Args...> fmt, Args &&...args)
{
    spdlog::default_logger_raw()->trace(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void debug(format_string_t<Args...> fmt, Args &&...args)
{
    spdlog::default_logger_raw()->debug(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void info(format_string_t<Args...> fmt, Args &&...args)
{
    spdlog::default_logger_raw()->info(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void warn(format_string_t<Args...> fmt, Args &&...args)
{
    spdlog::default_logger_raw()->warn(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void error(format_string_t<Args...> fmt, Args &&...args)
{
    spdlog::default_logger_raw()->error(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void critical(format_string_t<Args...> fmt, Args &&...args)
{
    spdlog::default_logger_raw()->critical(fmt, std::forward<Args>(args)...);
}

template <typename T>
inline void log(spdlog::source_loc location, spdlog::level::level_enum lvl, const T &msg)
{
    spdlog::default_logger_raw()->log(location, lvl, msg);
}

template <typename T>
inline void log(spdlog::level::level_enum lvl, const T &msg)
{
    spdlog::default_logger_raw()->log(lvl, msg);
}

} // namespace log
} // namespace bast

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#define LOG_LOGGER_TRACE(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#define LOG_TRACE(...) LOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define LOG_LOGGER_TRACE(logger, ...) (void)0
#define LOG_TRACE(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#define LOG_LOGGER_DEBUG(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#define LOG_DEBUG(...) LOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define LOG_LOGGER_DEBUG(logger, ...) (void)0
#define LOG_DEBUG(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#define LOG_LOGGER_INFO(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::info, __VA_ARGS__)
#define LOG_INFO(...) LOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define LOG_LOGGER_INFO(logger, ...) (void)0
#define LOG_INFO(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#define LOG_LOGGER_WARN(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#define LOG_WARN(...) LOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define LOG_LOGGER_WARN(logger, ...) (void)0
#define LOG_WARN(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#define LOG_LOGGER_ERROR(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::err, __VA_ARGS__)
#define LOG_ERROR(...) LOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define LOG_LOGGER_ERROR(logger, ...) (void)0
#define LOG_ERROR(...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#define LOG_LOGGER_CRITICAL(logger, ...) SPDLOG_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)
#define LOG_CRITICAL(...) LOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)
#else
#define LOG_LOGGER_CRITICAL(logger, ...) (void)0
#define LOG_CRITICAL(...) (void)0
#endif