cmake_minimum_required(VERSION 3.22)
project(Insiemi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Insiemi
        set.h
        tester.cpp)
