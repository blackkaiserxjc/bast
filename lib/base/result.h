#pragma once

#include <boost/mp11.hpp>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <exception>
#include <source_location>
#include <system_error>
#include <type_traits>
#include <variant>

namespace bast {
namespace base {

using in_place_value_t = std::in_place_index_t<0>;
constexpr in_place_value_t in_place_value{};
using in_place_error_t = std::in_place_index_t<1>;
constexpr in_place_error_t in_place_error{};

namespace detail {

template <class... T>
using is_errc_t = std::is_same<boost::mp11::mp_list<std::remove_cvref_t<T>...>, boost::mp11::mp_list<std::errc>>;

template <class T>
inline constexpr bool is_errc_v = is_errc_t<T>::value;

} // namespace detail

template <class E>
class bad_result_access;

template <>
class bad_result_access<void> : public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return "bad result access";
    }
};

template <class Error>
class bad_result_access : public bad_result_access<void>
{
public:
    using error_type = Error;

    explicit bad_result_access(const Error &e)
        : bad_result_access<void>(), e_(e)
    {
    }

    error_type &&error() &&
    {
        return std::move(e_);
    }

    error_type &error() &
    {
        return e_;
    }

    const error_type &error() const &
    {
        return e_;
    }

private:
    error_type e_;
};

template <class Error>
struct error_traits
{
    template <class Exception>
    static Error make_error(Exception const &e)
    {
        return static_cast<Error>(e);
    }

    static Error make_error_from_current_exception()
    {
        try
        {
            throw;
        }
        catch (std::exception &e)
        {
            return make_error<Error>(e);
        }
        catch (...)
        {
            return Error();
        }
    }

    static void rethrow(Error const &e)
    {
        throw bad_result_access<Error>(e);
    }
};

template <>
struct error_traits<std::exception_ptr>
{
    template <class Exception>
    static std::exception_ptr make_error(Exception const &e)
    {
        return std::make_exception_ptr(e);
    }

    static std::exception_ptr make_error_from_current_exception()
    {
        return std::current_exception();
    }

    static void rethrow(std::exception_ptr const &e)
    {
        std::rethrow_exception(e);
    }
};

template <>
struct error_traits<std::error_code>
{
    template <class Exception>
    static std::error_code make_error(Exception const &e)
    {
        return std::make_error_code(e);
    }

    static std::error_code make_error(std::system_error const &e)
    {
        return e.code();
    }

    static std::error_code make_error_from_current_exception()
    {
        try
        {
            throw;
        }
        catch (std::system_error &e)
        {
            return make_error(e);
        }
        catch (...)
        {
            return {};
        }
    }

    static void rethrow(std::error_code const &e)
    {
        throw std::system_error(e);
    }
};

template <class T, class E = std::error_code>
class result
{
public:
    using value_type = T;
    using error_type = E;

    template <class En2 = void, class En = typename std::enable_if_t<std::is_void_v<En2> && std::is_default_constructible_v<T>>>
    constexpr result() noexcept(std::is_nothrow_default_constructible_v<T>)
        : v_(in_place_value)
    {
    }

    template <class A = T, typename std::enable_if_t<std::is_convertible_v<A, T> && !(detail::is_errc_v<A> && std::is_arithmetic_v<T>)&&std::is_constructible_v<E, A>, int> = 0>
    constexpr explicit result(A &&a) noexcept(std::is_nothrow_constructible_v<T, A>)
        : v_(in_place_value, std::forward<A>(a))
    {
    }

    template <class A = E, class = void, typename std::enable_if_t<std::is_convertible_v<A, E> && !std::is_constructible_v<T, A>, int> = 0>
    constexpr explicit result(A &&a) noexcept(std::is_nothrow_constructible_v<E, A>)
        : v_(in_place_error, std::forward<A>(a))
    {
    }

    template <class... A, class En = typename std::enable_if_t<std::is_constructible_v<T, A...> && !(detail::is_errc_v<A...> && std::is_arithmetic_v<T>)&&!std::is_constructible_v<E, A...>>>
    constexpr explicit result(A &&...a) noexcept(std::is_nothrow_constructible_v<T, A...>)
        : v_(in_place_value, std::forward<A>(a)...)
    {
    }

    template <class... A, class En2 = void, class En = typename std::enable_if_t<!std::is_constructible_v<T, A...> && std::is_constructible_v<E, A...>>>
    constexpr explicit result(A &&...a) noexcept(std::is_nothrow_constructible_v<E, A...>)
        : v_(in_place_error, std::forward<A>(a)...)
    {
    }

    template <class... A, class En = typename std::enable_if_t<std::is_constructible_v<T, A...>>>
    constexpr explicit result(in_place_value_t, A &&...a) noexcept(std::is_nothrow_constructible_v<T, A...>)
        : v_(in_place_value, std::forward<A>(a)...)
    {
    }

    template <class... A, class En = typename std::enable_if_t<std::is_constructible_v<E, A...>>>
    constexpr explicit result(in_place_error_t, A &&...a) noexcept(std::is_nothrow_constructible_v<E, A...>)
        : v_(in_place_error, std::forward<A>(a)...)
    {
    }

    [[nodiscard]] constexpr bool has_value() const noexcept
    {
        return v_.index() == 0;
    }

    [[nodiscard]] constexpr bool has_error() const noexcept
    {
        return v_.index() != 0;
    }

    constexpr explicit operator bool() const noexcept
    {
        return v_.index() == 0;
    }

    constexpr T &value(std::source_location const &location = std::source_location::current()) &
    {
        if (has_value())
        {
            return std::get<0>(v_);
        }
        else
        {
            error_traits<error_type>::rethrow(error());
        }
    }

    constexpr T const &value(std::source_location const &location = std::source_location::current()) const &
    {
        if (has_value())
        {
            return std::get<0>(v_);
        }
        else
        {
            error_traits<error_type>::rethrow(error());
        }
    }

    template <class U = T>
    constexpr typename std::enable_if_t<std::is_move_constructible_v<U>, T>
    value(std::source_location const &location = std::source_location::current()) &&
    {
        return std::move(value(location));
    }

    template <class U = T>
    constexpr typename std::enable_if_t<!std::is_move_constructible_v<U>, T &&>
    value(std::source_location const &location = std::source_location::current()) &&
    {
        return std::move(value(location));
    }

    template <class U = T>
    constexpr typename std::enable_if_t<std::is_move_constructible_v<U>, T>
    value() const && = delete;

    template <class U = T>
    constexpr typename std::enable_if_t<std::is_move_constructible_v<U>, T const &&>
    value(std::source_location const &location = std::source_location::current())
    {
        return std::move(value(location));
    }

    constexpr T *operator->() noexcept
    {
        return std::get_if<0>(&v_);
    }

    constexpr T const *operator->() const noexcept
    {
        return std::get_if<0>(&v_);
    }

    constexpr T &operator*() &noexcept
    {
        auto p = operator->();
        assert(p != nullptr);
        return *p;
    }

    constexpr T const &operator*() const &noexcept
    {
        T const *p = operator->();
        assert(p != nullptr);
        return *p;
    }

    template <class U = T>
    constexpr
        typename std::enable_if_t<std::is_move_constructible_v<U>, T>::type
        operator*() &&noexcept(std::is_nothrow_move_constructible_v<T>)
    {
        return std::move(**this);
    }

    template <class U = T>
    constexpr
        typename std::enable_if_t<!std::is_move_constructible_v<U>, T &&>
        operator*() &&noexcept
    {
        return std::move(**this);
    }

    template <class U = T>
    constexpr
        typename std::enable_if_t<std::is_move_constructible_v<U>, T>
        operator*() const &&noexcept = delete;

    template <class U = T>
    constexpr
        typename std::enable_if_t<!std::is_move_constructible_v<U>, T const &&>
        operator*() const &&noexcept
    {
        return std::move(**this);
    }

    constexpr E error() const
        noexcept(std::is_nothrow_default_constructible_v<E> &&std::is_nothrow_copy_constructible_v<E>)
    {
        return has_error() ? std::get<1>(v_) : E();
    }

    constexpr void swap(result &r)
    {
        v_.swap(r.v_);
    }

    friend constexpr void swap(result &lhs, result &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    friend constexpr bool operator==(result const &lhs, result const &rhs) noexcept
    {
        return lhs.v_ == rhs.v_;
    }

    friend constexpr bool operator!=(result const &lhs, result const &rhs) noexcept
    {
        return lhs.v_ != rhs.v_;
    }

private:
    std::variant<T, E> v_;
};

template <class Ch, class Tr, class T, class E>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, result<T, E> const &r)
{
    if (r.has_value())
    {
        os << "value:" << *r;
    }
    else
    {
        os << "error:" << r.error();
    }
    return os;
}

template <class E>
class result<void, E>
{
public:
    constexpr result() noexcept
        : v_(in_place_value)
    {
    }

    template <class T>
    explicit constexpr result(T &&e) noexcept(std::is_nothrow_constructible_v<E, T>)
        : v_(in_place_error, std::forward<T>(e))
    {
    }

    template <class A, class En2 = void, class En = typename std::enable_if_t<std::is_convertible_v<A, E>>>
    constexpr explicit result(A &&a) noexcept(std::is_nothrow_constructible<E, A>::value)
        : v_(in_place_error, std::forward<A>(a))
    {
    }

    template <class... A, class En2 = void, class En3 = void, class En = typename std::enable_if_t<std::is_constructible_v<E, A...> && sizeof...(A) >= 2>>
    constexpr explicit result(A &&...a) noexcept(std::is_nothrow_constructible_v<E, A...>)
        : v_(in_place_error, std::forward<A>(a)...)
    {
    }

    constexpr explicit result(in_place_value_t) noexcept
        : v_(in_place_value)
    {
    }

    template <class... A, class En = typename std::enable_if_t<std::is_constructible_v<E, A...>>>
    constexpr explicit result(in_place_error_t, A &&...a) noexcept(std::is_nothrow_constructible_v<E, A...>)
        : v_(in_place_error, std::forward<A>(a)...)
    {
    }

    [[nodiscard]] constexpr bool has_value() const noexcept
    {
        return v_.index() == 0;
    }

    [[nodiscard]] constexpr bool has_error() const noexcept
    {
        return v_.index() != 0;
    }

    constexpr explicit operator bool() const noexcept
    {
        return v_.index() == 0;
    }

    constexpr void value(std::source_location const &location)
    {
    }

    constexpr void *operator->() noexcept
    {
        return std::get_if<0>(v_);
    }

    constexpr void const *operator->() const noexcept
    {
        return std::get_if<0>(&v_);
    }

    constexpr void operator*() const noexcept
    {
        assert(has_value());
    }

    constexpr E error() const
        noexcept(std::is_nothrow_default_constructible_v<E> &&std::is_nothrow_copy_constructible_v<E>)
    {
        return has_error() ? std::get<1>(v_) : E();
    }

    constexpr void swap(result &r) noexcept
    {
        v_.swap(r.v_);
    }

    friend constexpr void swap(result &lhs, result &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    friend constexpr bool operator==(result const &lhs, result const &rhs)
    {
        return lhs.v_ == rhs.v_;
    }

    friend constexpr bool operator!=(result const &lhs, result const &rhs)
    {
        return lhs.v_ != rhs.v_;
    }

private:
    std::variant<std::monostate, E> v_;
};

} // namespace base
} // namespace bast

template <class Char, class T, class E>
struct fmt::formatter<bast::base::result<T, E>, Char> : basic_ostream_formatter<Char>
{
};

template <class Char, class E>
struct fmt::formatter<bast::base::result<void, E>, Char> : basic_ostream_formatter<Char>
{
};
