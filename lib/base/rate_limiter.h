#pragma once

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

namespace bast {
namespace base {

enum RateLimiterType
{
    kFixedWindow,
    kSlidingWindow,
    kTokenBucket,
};

class rate_limiter
{
public:
    static std::shared_ptr<rate_limiter> create(RateLimiterType type, std::size_t capacity, std::chrono::duration<double> time_unit = 60s);

    virtual bool is_allowed() = 0;
    virtual ~rate_limiter() noexcept = default;
};

} // namespace base
} // namespace bast