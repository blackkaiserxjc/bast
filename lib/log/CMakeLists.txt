find_package(spdlog CONFIG REQUIRED)

set(log_SRCS
        log.h
        setup.h)

add_library(bast_log INTERFACE ${log_SRCS})
add_library(bast::log ALIAS bast_log)

if (ENABLE_TESTING)
    add_subdirectory(test)
endif ()