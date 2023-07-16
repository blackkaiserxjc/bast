#include "rate_limiter.h"

#include <base/detail/fixed_window_rate_limiter.h>
#include <base/detail/sliding_window_rate_limiter.h>
#include <base/detail/token_bucket_rate_limiter.h>

namespace bast {
namespace base {

std::shared_ptr<rate_limiter> rate_limiter::create(
    bast::base::RateLimiterType type,
    size_t capacity,
    std::chrono::duration<double> time_unit)
{
    switch (type)
    {
    case RateLimiterType::kFixedWindow:
        return std::make_shared<fixed_window_rate_limiter>(capacity, time_unit);
    case RateLimiterType::kSlidingWindow:
        return std::make_shared<sliding_window_rate_limiter>(capacity, time_unit);
    case RateLimiterType::kTokenBucket:
        return std::make_shared<token_bucket_rate_limiter>(capacity, time_unit);
    }
    return std::make_shared<token_bucket_rate_limiter>(capacity, time_unit);
}

} // namespace base
} // namespace bast
