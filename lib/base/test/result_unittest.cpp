#include <base/result.h>
#include <catch2/catch_test_macros.hpp>

#include <charconv>
#include <memory>
#include <string_view>
#include <system_error>

struct X
{
    static int instances;
    int v_;
    explicit X(int v)
        : v_(v)
    {
        ++instances;
    }
    X(int v1, int v2)
        : v_(v1 + v2)
    {
        ++instances;
    }
    X(int v1, int v2, int v3)
        : v_(v1 + v2 + v3)
    {
        ++instances;
    }
    X(X const &) = delete;
    X &operator=(X const &) = delete;
    ~X()
    {
        --instances;
    }
};
int X::instances = 0;

TEST_CASE("result value construct", "[base][result][result-value-construct]")
{
    using namespace bast::base;
    {
        result<int> r(0);

        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(r.value() == 0);
    }
    {
        result<int> r{0};

        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(r.value() == 0);
    }

    {
        result<int, int> r(in_place_value, 1);

        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(*r == 1);
    }

    REQUIRE(X::instances == 0);

    {
        result<X> r(1);

        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(r.value().v_ == 1);

        REQUIRE(X::instances == 1);
    }

    REQUIRE(X::instances == 0);
    {
        result<X> r(1);

        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(r.value().v_ == 1);

        REQUIRE(X::instances == 1);
    }
}

TEST_CASE("result value access test case", "[base][result][result-value-access]")
{
    using namespace bast::base;
    {
        result<int> r;
        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(r);

        REQUIRE(r.value() == 0);
        REQUIRE(*r == 0);

        REQUIRE(r.operator->() == &*r);
    }
    {
        result<int> const r;
        REQUIRE(r.has_value());
        REQUIRE(!r.has_error());

        REQUIRE(r);

        REQUIRE(r.value() == 0);
        REQUIRE(*r == 0);

        REQUIRE(r.operator->() == &*r);
    }

    {
        auto ec = std::make_error_code(std::errc::invalid_argument);
        result<int> r(ec);

        REQUIRE(!r.has_value());
        REQUIRE(r.has_error());

        REQUIRE(!r);

        REQUIRE(r.operator->() == static_cast<int *>(0));
        REQUIRE(r.error() == ec);
    }
}

TEST_CASE("result map test case", "[base][result][map]")
{
    using namespace bast::base;
    {
        result<int> r(42);
        auto mapped = r.map([](int i) -> int {
            return i * 2;
        });
        REQUIRE(!!mapped);
        REQUIRE(mapped.has_value());
        REQUIRE(!mapped.has_error());
        REQUIRE(mapped.value() == 42 * 2);
    }
    {
        result<std::unique_ptr<int>> r{std::make_unique<int>(42)};
        auto mapped = std::move(r).map([](std::unique_ptr<int> i) -> int {
            return *i;
        });
        REQUIRE(!!mapped);
        REQUIRE(mapped.has_value());
        REQUIRE(!mapped.has_error());
        REQUIRE(mapped.value() == 42);
    }
}

TEST_CASE("result and_then test case", "[base][result][and_then]")
{
    using namespace bast::base;
    {
        result<int> r(42);
        auto mapped = r.and_then([](int i) -> result<int> {
            return result<int>(i * 2);
        });
        REQUIRE(!!mapped);
        REQUIRE(mapped.has_value());
        REQUIRE(!mapped.has_error());
        REQUIRE(mapped.value() == 84);
    }
    {
        result<std::string_view> r("42");
        auto mapped = r.and_then([](std::string_view sv) -> result<int> {
                           int r{};
                           auto [ptr, ec]{std::from_chars(sv.data(), sv.data() + sv.size(), r)};
                           if (ec == std::errc())
                               return result<int>{r};
                           else
                               return result<int>{std::make_error_code(std::errc::invalid_argument)};
                       })
                          .map([](int n) { return n + 1; })
                          .map([](int n) { return std::to_string(n); });
        REQUIRE(!!mapped);
        REQUIRE(mapped.has_value());
        REQUIRE(mapped.value() == "43");
    }
}

TEST_CASE("result or_else test case", "[base][result][or_else]")
{
    using namespace bast::base;
    {
        result<int> r(42);
        auto mapped = r.or_else([](auto ec) -> result<int> {
            return std::make_error_code(std::errc::invalid_argument);
        });
        REQUIRE(!!mapped);
        REQUIRE(mapped.has_value());
        REQUIRE(!mapped.has_error());
    }
}
