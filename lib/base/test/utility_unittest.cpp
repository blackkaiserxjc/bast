#include <catch2/catch_test_macros.hpp>

#include <base/utility.h>
#include <string_view>
using namespace bast;
namespace {
void f(int &i)
{
    i += 1;
}

static int j = 0;

void g()
{
    j += 1;
}

} // namespace

TEST_CASE("finally_lambda test", "[base][utility][finally_lambda]")
{
    int i = 0;
    {
        auto _ = base::finally([&]() { f(i); });
        REQUIRE(i == 0);
    }
    REQUIRE(i == 1);
}

TEST_CASE("finally_lambda_move test", "[base][utility][finally_lambda_move]")
{
    int i = 0;
    {
        auto _1 = base::finally([&]() { f(i); });
        {
            auto _2 = std::move(_1);
            REQUIRE(i == 0);
        }
        REQUIRE(i == 1);
        {
            auto _2 = std::move(_1);
            REQUIRE(i == 1);
        }
    }
}

TEST_CASE("finally_const_lvalue_lambda test", "[base][utility][finally_const_lvalue_lambda]")
{
    int i = 0;
    {
        const auto const_lvalue_lambda = [&]() { f(i); };
        auto _ = base::finally(const_lvalue_lambda);
        REQUIRE(i == 0);
    }
    REQUIRE(i == 1);
}

TEST_CASE("finally_mutable_lvalue_lambda test", "[base][utility][finally_mutable_lvalue_lambda]")
{
    int i = 0;
    {
        auto mutable_lvalue_lambda = [&]() { f(i); };
        auto _ = base::finally(mutable_lvalue_lambda);
        REQUIRE(i == 0);
    }
    REQUIRE(i == 1);
}

TEST_CASE("finally_function_ptr test", "[base][utility][finally_function_ptr]")
{
    j = 0;
    {
        auto _ = base::finally(&g);
        REQUIRE(j == 0);
    }
    REQUIRE(j == 1);
}

TEST_CASE("finally_function test", "[base][utility][finally_function]")
{
    j = 0;
    {
        auto _ = base::finally(g);
        REQUIRE(j == 0);
    }
    REQUIRE(j == 1);
}
