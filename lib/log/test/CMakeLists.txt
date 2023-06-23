find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

set(bast_log_unittest_SRCS basic_unittest.cpp)

add_executable(bast_log_unittest ${bast_log_unittest_SRCS})
target_link_libraries(bast_log_unittest
        Catch2::Catch2
        Catch2::Catch2WithMain
        spdlog::spdlog
        spdlog::spdlog_header_only
        bast::log
        Threads::Threads)
