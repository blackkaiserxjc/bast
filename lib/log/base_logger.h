#pragma once

#include <spdlog/spdlog.h>
#include <string_view>

using namespace std::string_view_literals;

namespace bast {
namespace log {

enum levels
{
    trace = spdlog::level::trace,
    debug = spdlog::level::debug,
    info = spdlog::level::info,
    warn = spdlog::level::warn,
    error = spdlog::level::err,
    crit = spdlog::level::critical,
    off = spdlog::level::off
};

class logger
{
public:
    spdlog::string_view_t level_string() const
    {
        return spdlog::level::level_string_views[logger_->level()];
    }

    std::string name() const
    {
        return logger_->name();
    }

    void set_level(spdlog::level::level_enum level)
    {
        logger_->set_level(level);
    }

    spdlog::level::level_enum level() const
    {
        return logger_->level();
    }

    spdlog::logger &get_logger()
    {
        return *logger_;
    }

    template <typename... Args>
    void log(spdlog::source_loc loc, spdlog::level::level_enum lvl, std::string_view fmt, const Args &...args)
    {
        logger_->log(loc, lvl, fmt, args...);
    }

    static inline constexpr std::string_view default_log_format = "[%Y-%m-%d %T.%e][%t][%l][%n] [%g:%#] %v"sv;

protected:
    logger(std::shared_ptr<spdlog::logger> logger);

private:
    std::shared_ptr<spdlog::logger> logger_;
};

} // namespace log
} // namespace bast