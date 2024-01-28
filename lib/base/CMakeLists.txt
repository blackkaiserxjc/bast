find_package(Boost REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(xxHash CONFIG REQUIRED)

set(base_SRCS
        base64.h
        base64.cpp
        crc.h
        error_types.h
        hash.h
        ioc_container.h
        ioc_container.cpp
        lazy.h
        random.h
        random.cpp
        result.h
        type.h
        type_traits.h
        rate_limiter.h
        rate_limiter.cpp
        snowflake.h
        utility.h
)

set(base_detail_SRCS
        detail/crc_table.h
        detail/ioc_container.h
        detail/base64.h
        detail/base64.cpp
        detail/fixed_window_rate_limiter.h
        detail/fixed_window_rate_limiter.cpp
        detail/sliding_window_rate_limiter.h
        detail/sliding_window_rate_limiter.cpp
        detail/token_bucket_rate_limiter.h
        detail/token_bucket_rate_limiter.cpp
)

add_library(bast_base
    ${base_SRCS}
    ${base_detail_SRCS}
)
add_library(bast::base ALIAS bast_base)

# target depend libraries
target_link_libraries(bast_base PRIVATE
        Boost::boost
        fmt::fmt-header-only
        xxHash::xxhash
)

if (BUILD_TESTING)
    add_subdirectory(test)
endif ()
