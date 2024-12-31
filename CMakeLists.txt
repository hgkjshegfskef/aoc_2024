cmake_minimum_required(VERSION 3.30)
project(aoc_2024)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

add_library(util util.cc)
target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(util PUBLIC AOC_USE_RANGES)

add_executable(01_p1 01_p1.cpp)
target_link_libraries(01_p1 PRIVATE util fmt::fmt)

configure_file(${CMAKE_SOURCE_DIR}/01_p1.in ${CMAKE_BINARY_DIR}/01_p1.in)
