#pragma once

#include <error/error.h>

#include <boost/system/system_error.hpp>
#include <string>

namespace boost {
namespace system {

template <>
struct is_error_code_enum<::bast::cli::error>
{
    static bool const value = true;
};

template <>
struct is_error_condition_enum<::bast::cli::condition>
{
    static bool const value = true;
};

} // namespace system
} // namespace boost

namespace bast {
namespace cli {
namespace detail {

struct BOOST_SYMBOL_VISIBLE error_cat_type : boost::system::error_category
{
    const char *name() const noexcept override;

    std::string message(int code) const override;
    char const *message(int code,
        char *,
        std::size_t) const noexcept override;

    boost::system::error_condition
    default_error_condition(
        int ev) const noexcept override;

    constexpr error_cat_type() noexcept
        : error_category(0xbc15399d7a4ce829)
    {
    }
};

struct BOOST_SYMBOL_VISIBLE condition_cat_type : boost::system::error_category
{
    const char *name() const noexcept override;

    std::string message(int code) const override;
    char const *message(int code,
        char *,
        std::size_t) const noexcept override;

    constexpr condition_cat_type() noexcept
        : error_category(0xbc15399d7a4ce829)
    {
    }
};

extern error_cat_type error_cat;
extern condition_cat_type condition_cat;

} // namespace detail

inline boost::system::error_code make_error_code(error ev) noexcept
{
    return boost::system::error_code{
        static_cast<std::underlying_type<error>::type>(ev),
        detail::error_cat};
}

inline boost::system::error_condition make_error_condition(condition c) noexcept
{
    return boost::system::error_condition{
        static_cast<std::underlying_type<condition>::type>(c),
        detail::condition_cat};
}

} // namespace cli
} // namespace bast