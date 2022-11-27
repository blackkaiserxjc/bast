#include <boost/test/unit_test.hpp>

#include <base/crc.h>
#include <string_view>
using namespace bast;

constexpr uint32_t crc32(std::string_view str)
{
    base::crc<32> crc;
    crc.update(str);
    return crc.checksum();
}

BOOST_AUTO_TEST_SUITE(CRC)

BOOST_AUTO_TEST_CASE(CompileTimeTest)
{
    static_assert(crc32("123456789") == 0xCBF43926);
}

BOOST_AUTO_TEST_SUITE_END()