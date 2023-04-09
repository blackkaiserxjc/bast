#include <boost/test/unit_test.hpp>
#include <log/log.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

BOOST_AUTO_TEST_SUITE(BasicTest)

BOOST_AUTO_TEST_CASE(Macros)
{
    {
        LOG_TRACE("Test Macros Message1");
        LOG_DEBUG("Test Macros Message2");
        LOG_INFO("Test  Macros Message3");
        LOG_WARN("Test Macros Message4");
        LOG_ERROR("Test Macros Message5");
        LOG_CRITICAL("Test Macros Message6");
    }
    {
        LOG_TRACE("Test Macros Format {}", "Message1");
        LOG_DEBUG("Test Macros Format {}", "Message2");
        LOG_INFO("Test Macros Format {}", "Message3");
        LOG_WARN("Test Macros Format{}", "Message4");
        LOG_ERROR("Test Macros Format {}", "Message5");
        LOG_CRITICAL("Test Macros Format {}", "Message6");
    }
    {
    }
}
BOOST_AUTO_TEST_SUITE_END()