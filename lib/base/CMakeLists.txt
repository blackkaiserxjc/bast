find_package(Boost REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(base_SRCS
    base64.h
    base64.cpp
    crc.h
    ioc_container.h
    ioc_container.cpp
    random.h
    random.cpp
)

set(base_detail_SRCS
    detail/crc_table.h
    detail/ioc_container.h
    detail/base64.h
    detail/base64.cpp
)

add_library(bast_base
    ${base_SRCS}
    ${base_detail_SRCS}
)
add_library(bast::base ALIAS bast_base)

if(ENABLE_TESTING)
    add_subdirectory(test)
endif()
