
#pragma once

#include <boost/system/error_code.hpp>
#include <boost/system/result.hpp>
#include <boost/system/system_category.hpp>

namespace bast {
namespace error_types {

using error_category = boost::system::error_category;

using error_code = boost::system::error_code;

using error_condition = boost::system::error_condition;

using system_error = boost::system::system_error;

using boost::system::generic_category;

using boost::system::system_category;

namespace errc = boost::system::errc;

template <class T>
using result = boost::system::result<T, error_code>;

} // namespace error_types

using namespace error_types;

} // namespace bast