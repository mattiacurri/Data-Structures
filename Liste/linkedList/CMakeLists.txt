cmake_minimum_required(VERSION 3.22)
project(linkedList)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(6
        linkedList.h
        test.cpp)
