#include "token_bucket_rate_limiter.h"

namespace bast {
namespace base {

token_bucket_rate_limiter::token_bucket_rate_limiter(
    std::size_t capacity,
    std::chrono::duration<double> time_unit)
    : capacity_(capacity),
      last_time_(std::chrono::steady_clock::now()),
      time_unit_(time_unit),
      tokens_((double)capacity_)
{
}

bool token_bucket_rate_limiter::is_allowed()
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_time_);
    tokens_ += capacity_ * (duration / time_unit_);
    if (tokens_ > capacity_)
    {
        tokens_ = (double)capacity_;
    }
    last_time_ = now;
    if (tokens_ > 1.0)
    {
        tokens_ -= 1.0;
        return true;
    }
    return false;
}

} // namespace base
} // namespace bast