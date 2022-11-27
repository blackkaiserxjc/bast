#pragma once

#include <climits>
#include <concepts>

#include <base/detail/crc_table.h>

namespace bast {
namespace base {

template <std::size_t Bits>
class crc
{
public:
    using value_type = typename detail::crc_table<Bits>::value_type;

    /**
     * 构造函数
     */
    constexpr crc() noexcept
        : rem_{detail::crc_table<Bits>::init_rem}
    {
    }

    /**
     * 析构函数
     */
    ~crc()

        noexcept =
        default;

    /**
     * 重置状态
     */
    void reset()
    {
        rem_ = detail::crc_table<Bits>::init_rem;
    }

    /**
     * 数值类型更新
     * @param b 单字节
     */
    constexpr void update(std::byte b)
    {
        update(static_cast<std::uint8_t>(b));
    }

    /**
     * 数值类型更新
     * @param value 数值
     */
    template <typename T>
        requires std::signed_integral<T>
    constexpr void update(T value) noexcept
    {
        update(std::make_unsigned_t<T>(value));
    }

    /**
     * 数值类型更新
     * @param value 数值
     */
    template <typename T>
        requires std::unsigned_integral<T>
    constexpr void update(T value) noexcept
    {
        [&]<std::size_t... N>(std::index_sequence<N...>)
        {
            ((rem_ = detail::crc_table<Bits>::update(rem_, static_cast<std::uint8_t>(value >> N * CHAR_BIT))), ...);
        }
        (std::make_index_sequence<sizeof(T)>{});
    }

    /**
     * 数值类型更新
     * @param value 数值
     */
    constexpr void update(float value) noexcept
    {
        union
        {
            float f;
            uint32_t i;
        } u{value};
        update(static_cast<uint32_t>(u.i));
    }

    /**
     * 数值类型更新
     * @param value 数值
     */
    constexpr void update(double value) noexcept
    {
        union
        {
            double d;
            uint64_t i;
        } u{value};
        update(static_cast<uint64_t>(u.i));
    }

    /**
     * 字符串更新
     * @param str 字符串
     */
    constexpr void update(std::string_view str) noexcept
    {
        for (auto c : str)
        {
            update(c);
        }
    }

    /**
     * 更新
     * @param data 数据
     * @param size 数据大小
     */
    void update(void const *data, std::size_t size)
    {
        auto const *start = static_cast<const std::uint8_t *>(data);
        auto const *end = start + size;
        for (auto p = start; p < end; ++p)
        {
            rem_ = detail::crc_table<Bits>::update(rem_, *p);
        }
    }

    /**
     * 获取校验和
     */
    constexpr value_type checksum() const
    {
        return detail::crc_table<Bits>::finalize(rem_);
    }

private:
    value_type rem_;
};

using crc16_type = crc<16>;
using crc32_type = crc<32>;
} // namespace base
} // namespace bast