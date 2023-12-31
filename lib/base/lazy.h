#pragma once

#include <optional>
#include <type_traits>
#include <utility>

namespace bast {
namespace base {
namespace detail {

template <class F>
struct basic_lazy
{
    using result_type = std::invoke_result_t<F>;

    static_assert(!std::is_const_v<F>, "F should not be a const-qualified type");
    static_assert(!std::is_reference_v<F>, "F should not be aa reference type");

    explicit basic_lazy(F &&f)
        : callable_(std::move(f))
    {
    }
    explicit basic_lazy(const F &f)
        : callable_(f)
    {
    }

    basic_lazy(basic_lazy &&o)
        : value_(std::move(o.value_)), callable_(std::move(o.callable_))
    {
    }

    basic_lazy(const basic_lazy &) = delete;
    basic_lazy &operator=(const basic_lazy &) = delete;
    basic_lazy &operator=(basic_lazy &&) = delete;

    const result_type &operator()() const
    {
        ensure_initialized();
        return *value_;
    }

    result_type &operator()()
    {
        ensure_initialized();
        return *value_;
    }

private:
    void ensure_initialized() const
    {
        if (!value_)
        {
            value_ = callable_();
        }
    }

    mutable std::optional<result_type> value_;
    mutable F callable_;
};

} // namespace detail

template <class F>
auto lazy(F &&f)
{
    return detail::basic_lazy<std::remove_cvref_t<F>>(std::forward<F>(f));
}

} // namespace base
} // namespace bast