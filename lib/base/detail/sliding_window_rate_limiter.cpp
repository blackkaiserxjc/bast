#include "sliding_window_rate_limiter.h"

#include <assert.h>

namespace bast {
namespace base {

sliding_window_rate_limiter::sliding_window_rate_limiter(
    std::size_t capacity,
    std::chrono::duration<double> time_unit)
    : capacity_(capacity),
      unit_start_time_(std::chrono::steady_clock::now()),
      last_time_(unit_start_time_),
      time_unit_(time_unit)
{
}

bool sliding_window_rate_limiter::is_allowed()
{
    auto now = std::chrono::steady_clock::now();
    unit_start_time_ = unit_start_time_ + std::chrono::duration_cast<decltype(unit_start_time_)::duration>(std::chrono::duration<double>(static_cast<double>((uint64_t)(std::chrono::duration_cast<std::chrono::duration<double>>(now - unit_start_time_).count() / time_unit_.count())) * time_unit_.count()));

    if (unit_start_time_ > last_time_)
    {
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(unit_start_time_ - last_time_);
        auto start_time = last_time_;
        if (duration >= time_unit_)
        {
            previous_requests_ = 0;
        }
        else
        {
            previous_requests_ = current_requests_;
        }
        current_requests_ = 0;
    }
    auto coef = std::chrono::duration_cast<std::chrono::duration<double>>(now - unit_start_time_) / time_unit_;
    assert(coef <= 1.0);

    auto count = previous_requests_ * (1.0 - coef) + current_requests_;
    if (count < capacity_)
    {
        current_requests_++;
        last_time_ = now;
        return true;
    }
    return false;
}

} // namespace base
} // namespace bast