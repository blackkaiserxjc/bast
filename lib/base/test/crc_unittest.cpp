#include <catch2/catch_test_macros.hpp>

#include <base/crc.h>
#include <string_view>
using namespace bast;

constexpr uint32_t crc32(std::string_view str)
{
    base::crc<32> crc;
    crc.update(str);
    return crc.checksum();
}

TEST_CASE("crc compile time case", "[base][crc][compile-time-test]")
{
    static_assert(crc32("123456789") == 0xCBF43926);
}