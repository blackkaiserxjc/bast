find_package(Boost REQUIRED
             COMPONENTS atomic
                        date_time
                        regex
                        system
                        thread
                        filesystem
                        log_setup
                        log
                        unit_test_framework)

find_package(fmt CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(bast_base_unittest_SRCS
    crc_unittest.cpp
    random_unittest.cpp
    result_unittest.cpp
    unittest_main.cpp
    ioc_unittest.cpp)

add_executable(bast_base_unittest ${bast_base_unittest_SRCS})

target_link_libraries(bast_base_unittest
                      bast::base
                      fmt::fmt
                      Boost::log_setup
                      Boost::log
                      Boost::atomic
                      Boost::date_time
                      Boost::filesystem
                      Boost::regex
                      Boost::system
                      Boost::thread
                      Boost::unit_test_framework
                      Threads::Threads)
