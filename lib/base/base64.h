#pragma once

#include <string>
#include <string_view>

namespace bast {
namespace base {

/**
 * base64编码
 * @param data 数据源
 * @return 编码后数据
 */
    std::string base64_encode(std::string_view data);

/**
 * base64解码
 * @param data
 * @return 解码后数据
 */
    std::string base64_decode(std::string_view data);
} // namespace base
} // namespace bast