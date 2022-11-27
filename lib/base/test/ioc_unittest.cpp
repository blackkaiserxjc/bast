#include <boost/test/unit_test.hpp>
#include <base/ioc_container.h>

BOOST_AUTO_TEST_SUITE(IocTest)

struct Interface
{
    virtual void Func() = 0;
    virtual ~Interface(){};
};

struct Derivedb : public Interface
{
    void Func() override
    {
    }
};

struct Bus
{
    void Func() const
    {
    }
};

struct Car
{
    Car(int i, float f, std::string str)
        : i(i), f(f), str(std::move(str))
    {
    }

    void Func() const
    {
    }
    int i;
    float f;
    std::string str;
};

BOOST_AUTO_TEST_CASE(Basic)
{
    using namespace bast::base;
    {
        ioc_container ioc;
        ioc.bind<Derivedb>();
        ioc.bind<Bus>();
        auto derive = ioc.load<Derivedb>();
        derive->Func();
        auto bus = ioc.load<Bus>();
        bus->Func();
    }

    {
        ioc_container ioc;
        ioc.bind<Car>(42, 3.14, "hello world");
        auto car = ioc.load<Car>();
        car->Func();
    }
}
BOOST_AUTO_TEST_SUITE_END()