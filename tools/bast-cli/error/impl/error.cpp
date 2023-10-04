#include "error.h"

namespace bast {
namespace cli {
namespace detail {

const char *error_cat_type::name() const noexcept
{
    return "bast.cli";
}

std::string error_cat_type::message(int code) const
{
    return message(code, nullptr, 0);
}

char const *error_cat_type::message(int code, char *, std::size_t) const noexcept
{
    switch (static_cast<bast::cli::error>(code))
    {
    case error::no_args:
        return "no args";
    case error::not_found_cmd:
        return "not found cmd";
    case error::success:
        return "success";
    }
    return nullptr;
}

boost::system::error_condition error_cat_type::default_error_condition(int ev) const noexcept
{
    switch (static_cast<error>(ev))
    {
    case error::no_args:
    case error::not_found_cmd:
        return condition::fatal;
    default:
        return {ev, *this};
    }
}

const char *condition_cat_type::name() const noexcept
{
    return "bast.cli";
}

std::string condition_cat_type::message(int code) const
{
    return message(code, nullptr, 0);
}

char const *condition_cat_type::message(int code, char *, std::size_t) const noexcept
{
    switch (static_cast<condition>(code))
    {
    default:
    case condition::fatal:
        return "fatal condition";
    }
}

#if defined(_MSC_VER) && _MSC_VER <= 1900
#pragma warning(push)
#pragma warning(disable : 4592)
#endif

error_cat_type error_cat;
condition_cat_type condition_cat;

#if defined(_MSC_VER) && _MSC_VER <= 1900
#pragma warning(pop)
#endif

} // namespace detail
} // namespace cli
} // namespace bast