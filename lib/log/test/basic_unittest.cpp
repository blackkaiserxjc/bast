#include <catch2/catch_test_macros.hpp>
#include <log/log.h>

TEST_CASE("log test case marcos", "[log][macros]")
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
}

TEST_CASE("log test case stdout ", "[log][stdout]")
{
    bast::log::trace("Test Stdout Trace Message");
    bast::log::debug("Test Stdout Debug Message");
    bast::log::info("Test Stdout Info Message");
    bast::log::warn("Test Stdout Warn Message");
    bast::log::error("Test Stdout Error Message");
    bast::log::critical("Test Stdout Critical Message");
}