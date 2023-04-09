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

} // namespace bast
