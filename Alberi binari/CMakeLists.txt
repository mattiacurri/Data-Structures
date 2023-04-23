cmake_minimum_required(VERSION 3.23)
project(Alberi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Alberi
        zero_one_binary_tree.h
        test.cpp
        )
