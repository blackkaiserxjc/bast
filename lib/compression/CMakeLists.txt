
set(compression_SRCS
        compressor.h
        decompressor.h
)

add_library(bast_compression INTERFACE ${compression_SRCS})
add_library(bast::compression ALIAS bast_compression)

if (BUILD_TESTING)
    add_subdirectory(test)
endif ()