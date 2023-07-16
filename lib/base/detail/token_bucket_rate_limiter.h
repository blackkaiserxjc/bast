#pragma once

#include <base/rate_limiter.h>

namespace bast {
namespace base {

class token_bucket_rate_limiter : public rate_limiter
{
public:
    token_bucket_rate_limiter(std::size_t capacity, std::chrono::duration<double> time_unit);

    bool is_allowed() override;
    ~token_bucket_rate_limiter() noexcept override = default;

private:
    std::size_t capacity_;
    std::chrono::steady_clock::time_point last_time_;
    std::chrono::duration<double> time_unit_;
    double tokens_;
};

} // namespace base
} // namespace bast
