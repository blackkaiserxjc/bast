
#include <base/snowflake.h>
#include <catch2/catch_test_macros.hpp>
#include <set>

TEST_CASE("snowflake generate test", "[base][snowflake][generate]")
{
    using bast::base::snowflake;
    std::set<std::uint64_t> result;
    auto id_generator = std::make_shared<snowflake>(1001, 1);
    for (int i = 0; i < 100; i++)
    {
        result.insert(id_generator->id());
    }
    REQUIRE(result.size() == 100);
}
