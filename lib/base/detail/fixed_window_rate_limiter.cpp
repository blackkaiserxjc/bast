#include "fixed_window_rate_limiter.h"

namespace bast {
namespace base {

fixed_window_rate_limiter::fixed_window_rate_limiter(
    std::size_t capacity,
    std::chrono::duration<double> time_unit)
    : capacity_(capacity),
      last_time_(std::chrono::steady_clock::now()),
      time_unit_(time_unit)
{
}

bool fixed_window_rate_limiter::is_allowed()
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_time_);
    if (duration >= time_unit_)
    {
        current_requests_ = 0;
        last_time_ = now;
    }
    if (current_requests_ < capacity_)
    {
        current_requests_++;
        return true;
    }
    return false;
}

} // namespace base
} // namespace bast