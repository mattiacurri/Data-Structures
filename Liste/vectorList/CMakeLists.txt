cmake_minimum_required(VERSION 3.23)
project(vectorList)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(vectorList
        exceptions.h
        tester.cpp
        vectorList.h)
