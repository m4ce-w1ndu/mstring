cmake_minimum_required(VERSION 3.8)
project(mstring-tests LANGUAGES C)

include_directories(lib/check/src)
add_subdirectory(lib/check)

add_executable(tests "test.c")
target_link_libraries(tests PUBLIC check)
target_link_libraries(tests PUBLIC mstring)