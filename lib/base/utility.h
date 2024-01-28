#pragma once

#include <utility>

namespace bast {
namespace base {

template <class F>
class final_action
{
public:
    explicit final_action(const F &f) noexcept
        : f{f}
    {
    }

    explicit final_action(F &&f) noexcept
        : f{std::move(f)}
    {
    }

    ~final_action() noexcept
    {
        if (invoke) f();
    }

    final_action(const final_action &) = default;
    void operator=(const final_action &) = delete;
    void operator=(final_action &&) = delete;

private:
    F f;
    bool invoke = true;
};

template <class F>
[[nodiscard]] auto finally(F &&f) noexcept
{
    return final_action<std::decay_t<F>>{std::forward<F>(f)};
}

} // namespace base
} // namespace bast