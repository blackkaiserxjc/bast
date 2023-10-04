find_package(Boost REQUIRED)

set(bootstrap_SRCS
        application.h
        application.cpp
        options.h
        options.cpp
)

add_library(bast_bootstrap ${bootstrap_SRCS})
add_library(bast::bootstrap ALIAS bast_bootstrap)

if (BUILD_TESTING)
    add_subdirectory(test)
endif ()