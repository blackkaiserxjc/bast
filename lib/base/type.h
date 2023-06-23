#pragma once

#include <cstdint>

namespace std {
using i8 [[maybe_unused]] = std::int8_t;
using i16 [[maybe_unused]] = std::int16_t;
using i32 [[maybe_unused]] = std::int32_t;
using i64 [[maybe_unused]] = std::int64_t;

using u8 [[maybe_unused]] = std::uint8_t;
using u16 [[maybe_unused]] = std::uint16_t;
using u32 [[maybe_unused]] = std::uint32_t;
using u64 [[maybe_unused]] = std::uint64_t;

using f32 [[maybe_unused]] = float;
using f64 [[maybe_unused]] = double;
} // namespace std
