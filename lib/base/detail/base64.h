#pragma once

#include <utility>

namespace bast {
namespace detail {
namespace base64 {

inline std::size_t constexpr encoded_size(std::size_t n)
{
    return 4 * ((n + 2) / 3);
}

inline std::size_t constexpr decoded_size(std::size_t n)
{
    return n / 4 * 3;
}

std::size_t encode(void *dest, void const *src, std::size_t length);

std::pair<std::size_t, std::size_t>
decode(void *dest, char const *src, std::size_t length);

} // namespace base64
} // namespace detail
} // namespace bast
