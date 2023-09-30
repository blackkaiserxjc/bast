find_package(Boost REQUIRED)

set(boot_SRCS
        application.h
        application.cpp
        options.h
        options.cpp
)

add_library(bast_boot ${boot_SRCS})
add_library(bast::boot ALIAS bast_boot)

if (BUILD_TESTING)
    add_subdirectory(test)
endif ()