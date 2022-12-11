#include <base/result.h>
#include <boost/test/unit_test.hpp>

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

BOOST_AUTO_TEST_SUITE(Result)

BOOST_AUTO_TEST_CASE(ResultValueConstruct)
{
    using namespace bast::base;
    {
        result<int> r(0);

        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_TEST(r.value() == 0);
    }
    {
        result<int> r{0};

        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_TEST(r.value() == 0);
    }

    {
        result<int, int> r(in_place_value, 1);

        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_CHECK_EQUAL(*r, 1);
    }

    BOOST_CHECK_EQUAL(X::instances, 0);

    {
        result<X> r(1);

        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_CHECK_EQUAL(r.value().v_, 1);

        BOOST_CHECK_EQUAL(X::instances, 1);
    }

    BOOST_CHECK_EQUAL(X::instances, 0);

    {
        result<X> r(1);

        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_CHECK_EQUAL(r.value().v_, 1);

        BOOST_CHECK_EQUAL(X::instances, 1);
    }
}

BOOST_AUTO_TEST_CASE(ResultValueAccess)
{
    using namespace bast::base;
    {
        result<int> r;
        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_TEST(r);

        BOOST_CHECK_EQUAL(r.value(), 0);
        BOOST_CHECK_EQUAL(*r, 0);

        BOOST_CHECK_EQUAL(r.operator->(), &*r);
    }
    {
        result<int> const r;
        BOOST_TEST(r.has_value());
        BOOST_TEST(!r.has_error());

        BOOST_TEST(r);

        BOOST_CHECK_EQUAL(r.value(), 0);
        BOOST_CHECK_EQUAL(*r, 0);

        BOOST_CHECK_EQUAL(r.operator->(), &*r);
    }

    {
        auto ec = std::make_error_code(std::errc::invalid_argument);
        result<int> r(ec);

        BOOST_TEST(!r.has_value());
        BOOST_TEST(r.has_error());

        BOOST_TEST(!r);

        BOOST_CHECK_EQUAL(r.operator->(), static_cast<int *>(0));
        BOOST_CHECK_EQUAL(r.error(), ec);
    }
}

BOOST_AUTO_TEST_CASE(ResultMap)
{
    using namespace
}

BOOST_AUTO_TEST_SUITE_END()
