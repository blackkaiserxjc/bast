#pragma once

#include <base/rate_limiter.h>

namespace bast {
namespace base {

class fixed_window_rate_limiter : public rate_limiter
{
public:
    fixed_window_rate_limiter(std::size_t capacity, std::chrono::duration<double> time_unit);

    bool is_allowed() override;
    ~fixed_window_rate_limiter() noexcept override = default;

private:
    std::size_t capacity_;
    std::size_t current_requests_;
    std::chrono::steady_clock::time_point last_time_;
    std::chrono::duration<double> time_unit_;
};

} // namespace base
} // namespace bast