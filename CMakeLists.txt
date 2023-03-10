cmake_minimum_required(VERSION 3.24)
project(lib264 C CXX)
enable_language(ASM)

set(LIB264_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIB264_CONFIG_DIR "${CMAKE_CURRENT_BINARY_DIR}")

if("${LIB264_ROOT}" STREQUAL "${LIB264_CONFIG_DIR}")
  message(
    FATAL_ERROR
      "Building from within the lib264 source tree is not supported.\n"
      "Hint: Run these commands\n"
      "$ rm -rf CMakeCache.txt CMakeFiles\n"
      "$ mkdir -p build\n"
      "$ cd build\n"
      "$ cmake ..\n"
      "Or re-run CMake from the build directory.")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(CMAKE_STATIC_LIBRARY_PREFIX "")

if(${CMAKE_CROSSCOMPILING})
  set(THREADS_PTHREAD_ARG
      "2"
      CACHE STRING
            "Refer https://gitlab.kitware.com/cmake/cmake/-/issues/16920" FORCE)
endif()

# Adds a target named 'ithread'
add_subdirectory(libthread lib EXCLUDE_FROM_ALL)

include("${LIB264_ROOT}/cmake/utils.cmake")

lib264_add_compile_options()
lib264_add_definitions()

include("${LIB264_ROOT}/common/common.cmake")
include("${LIB264_ROOT}/decoder/dec264.cmake")
include("${LIB264_ROOT}/test/decoder/app264.cmake")
