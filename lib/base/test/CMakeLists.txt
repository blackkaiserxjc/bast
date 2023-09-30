find_package(Boost REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(bast_base_unittest_SRCS
        crc_unittest.cpp
        random_unittest.cpp
        result_unittest.cpp
        ioc_unittest.cpp
        snowflake_unittest.cpp)

add_executable(bast_base_unittest ${bast_base_unittest_SRCS})

target_link_libraries(bast_base_unittest PRIVATE
        bast::base
        Boost::boost
        fmt::fmt
        Catch2::Catch2
        Catch2::Catch2WithMain
        Threads::Threads)
