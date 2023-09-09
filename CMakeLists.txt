cmake_minimum_required(VERSION 3.20)

project(bast LANGUAGES CXX)

if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif ()

if (POLICY CMP0057)
  cmake_policy(SET CMP0057 NEW)
endif ()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif ()

option(CMAKE_BUILD_TYPE "Build Type" "Debug")
option(BUILD_TESTING "Enable Testing" ON)

if (BUILD_TESTING)
  enable_testing()
  message(STATUS "Building with testing enabled")
else ()
  disable_testing()
  message(STATUS "Building with testing disabled")
endif ()

# platform
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /EHs /DEBUG /std:c++latest")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /GS /Od /MTd /bigobj")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Gy /MT /O2 -DNDEBUG /bigobj")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO /DEBUG")
  add_definitions(-D_WIN32_WINNT=0x0601
                  -DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
                  -D_SCL_SECURE_NO_WARNINGS
                  -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                  -D_CRT_SECURE_NO_WARNINGS
                  -D_DISABLE_EXTENDED_ALIGNED_STORAGE)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -g")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wvolatile -Wreturn-type")
  set(CMAKE_CXX_FLAGS_RELEASE
          "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG -Wvolatile -Wreturn-type")
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
endif()

#library
set(Boost_NO_WARN_NEW_VERSIONS 1)

# module path
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules"
    CACHE STRING "Modules for CMake" FORCE)

if (USE_PKG STREQUAL "VCPKG")
  #include(UseVcpkg)
endif ()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tools)
