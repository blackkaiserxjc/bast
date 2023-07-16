#pragma once

#include <base/rate_limiter.h>
#include <chrono>

namespace bast {
namespace base {

class sliding_window_rate_limiter : public rate_limiter
{
public:
    sliding_window_rate_limiter(std::size_t capacity, std::chrono::duration<double> time_unit);
    bool is_allowed() override;
    ~sliding_window_rate_limiter() noexcept override = default;

private:
    std::size_t capacity_;
    std::size_t current_requests_;
    std::size_t previous_requests_;
    std::chrono::steady_clock::time_point unit_start_time_;
    std::chrono::steady_clock::time_point last_time_;
    std::chrono::duration<double> time_unit_;
};

} // namespace base
} // namespace bast