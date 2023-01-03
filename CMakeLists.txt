cmake_minimum_required(VERSION 3.8)
project(mstring LANGUAGES C)

# Set basic compiler flags
if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /TC /Z7 /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "/Os /TC /MT")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address")
    set(CMAKE_CXX_FLAGS_DEBUG "-Os")
endif()

include_directories("src/include")

add_library(${CMAKE_PROJECT_NAME} "src/mstring.c" "src/include/mstring.h")