#include <log/base_logger.h>

namespace bast {
namespace log {

logger::logger(std::shared_ptr<spdlog::logger> logger)
    : logger_(logger)
{
    logger_->set_pattern(default_log_format.data());
    logger_->set_level(spdlog::level::info);
    logger_->flush_on(spdlog::level::critical);
}
} // namespace log
} // namespace bast
