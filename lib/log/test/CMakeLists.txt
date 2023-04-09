find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(bast_log_unittest_SRCS basic_unittest.cpp unittest_main.cpp)

add_executable(bast_log_unittest ${bast_log_unittest_SRCS})
target_link_libraries(bast_log_unittest
        spdlog::spdlog
        spdlog::spdlog_header_only
        bast::log
        Threads::Threads)
