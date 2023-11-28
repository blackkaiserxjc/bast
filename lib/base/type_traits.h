#pragma once

#include <type_traits>

namespace bast {

#if __cplusplus >= 201703L && defined(__cpp_lib_is_invocable) && __cpp_lib_is_invocable >= 201703

template <typename F, typename... Args>
using return_type_of_t = std::invoke_result_t<F, Args...>;

#else

template <typename F, typename... Args>
using return_type_of_t = typename std::result_of<F(Args...)>::type;

#endif

template <typename T, typename = void>
struct is_char_array_helper : std::false_type
{
};

template <std::size_t N>
struct is_char_array_helper<char[N], std::void_t<decltype(sizeof(declval<char[N]>()))>> : std::true_type
{
};

template <typename T>
constexpr bool is_char_array_v = is_char_array_helper<T>::value;

} // namespace bast
