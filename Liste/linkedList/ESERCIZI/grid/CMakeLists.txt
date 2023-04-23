cmake_minimum_required(VERSION 3.24)
project(grid)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(grid
        tester.cpp
        grid.h)
