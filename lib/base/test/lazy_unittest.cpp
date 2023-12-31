#include <functional>
#include <map>
#include <string>

#include <base/lazy.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("lazy test", "[base][lazy]")
{
    using bast::base::lazy;
    SECTION("basic_test")
    {
        int compute_count = 0;
        auto const val = lazy([&]() -> int {
            ++compute_count;
            REQUIRE(compute_count == 1);
            return 12;
        });
        REQUIRE(compute_count == 0);

        for (int i = 0; i < 100; ++i)
        {
            if (i > 50)
            {
                REQUIRE(val() == 12);
                REQUIRE(compute_count == 1);
            }
            else
            {
                REQUIRE(compute_count == 0);
            }
        }
        REQUIRE(val() == 12);
        REQUIRE(compute_count == 1);
    }

    SECTION("map_test")
    {
        auto lazy_map = lazy([]() -> std::map<std::string, std::string> {
            return {
                {"foo", "bar"},
                {"hello", "world"},
            };
        });
        REQUIRE(lazy_map().size() == 2);
        lazy_map()["key"] = "value";
        REQUIRE(lazy_map().size() == 3);
    }

    SECTION("const_test")
    {
        std::function<int()> const f = [&]() { return 12; };
        auto lz = lazy(f);
        REQUIRE(lz() == 12);
    }
}
