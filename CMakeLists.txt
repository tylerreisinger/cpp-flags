cmake_minimum_required(VERSION 2.4)
project(flags)

include_directories("src")
add_executable(flags-test test/unit.cpp test/flags.cpp)
target_link_libraries(flags-test gtest)
