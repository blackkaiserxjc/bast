find_package(spdlog CONFIG REQUIRED)

set(log_SRCS
        common.h
        log.h
        base_logger.h
        base_logger.cpp)

add_library(bast_log INTERFACE ${log_SRCS})
add_library(bast::log ALIAS bast_log)

if (BUILD_TESTING)
    add_subdirectory(test)
endif ()