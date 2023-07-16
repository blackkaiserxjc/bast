find_package(cxxopts CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)

set(bast_cli_SRCS
        version.h
        version.cpp
        main.cpp
        )

add_executable(bast_cli ${bast_cli_SRCS})
target_link_libraries(bast_cli PRIVATE cxxopts::cxxopts)
