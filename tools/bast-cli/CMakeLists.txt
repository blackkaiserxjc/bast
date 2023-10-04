find_package(cxxopts CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(bast_cli_SRCS
        main.cpp
        command/command.h
        command/command.cpp
        command/version.h
        command/version.cpp
        command/help.h
        command/help.cpp
        command/runner.h
        command/runner.cpp
        error/error.h
        error/error_types.h
        error/impl/error.h
        error/impl/error.cpp
)

add_executable(bast_cli ${bast_cli_SRCS})
target_link_libraries(bast_cli
        PRIVATE
        cxxopts::cxxopts
        fmt::fmt
)
